#include "scene.h"

#include <QDebug>
#include <QPointF>

#include "rigidbody.h"

Scene::Scene(QScrollBar *s, QObject *parent):QGraphicsScene(0, 0, 80000, 720, parent)
{
    scroll = s;
    velocity = 7;
    jumpHeight = 200;
    groundLevel = 660;

    // Description de l'animation de saut
    jumpAnimation = new QPropertyAnimation(this);
    jumpAnimation->setTargetObject(this);
    jumpAnimation->setPropertyName("jumpFactor");
    jumpAnimation->setStartValue(0);
    jumpAnimation->setKeyValueAt(0.5, 1);
    jumpAnimation->setEndValue(0);
    jumpAnimation->setDuration(800);
    jumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);

    connect(this, &Scene::jumpFactorChanged, this, &Scene::jumpPlayer);
    connect(jumpAnimation, &QPropertyAnimation::stateChanged, this, &Scene::jumpStatusChanged);

    // Timer pour le mouvement
    moveTimer = new QTimer(this);
    moveTimer->setInterval(20); // <--- durée d'une frame en ms (donc fps ~= 1000/20 = 50)
    connect(moveTimer, &QTimer::timeout, this, &Scene::movePlayer);

    // Timer pour la chute
    fallTimer = new QTimer(this);
    fallTimer->setInterval(20); // <--- durée d'une frame en ms
    connect(fallTimer, &QTimer::timeout, this, &Scene::fallPlayer);

    // Placement d'un bloc au sol sous le joueur
    RigidBody *rb = new RigidBody();
    addItem(rb);
    rb->setPos(0, groundLevel);
    lastPlatform = rb;

    player = new Player();
    addItem(player);
    player->setPos(25, groundLevel - player->boundingRect().height());

    // "Vue" de la scene ---> 8000 de long et 720 de haut
    setSceneRect(0, 0, 8000, 720);


    scroll->setValue(0);

    this->installEventFilter(this);
}

qreal Scene::getJumpFactor() const
{
    return jumpFactor;
}

void Scene::setJumpFactor(const qreal &newJumpFactor)
{
    if(jumpFactor == newJumpFactor) {
        return;
    }

    jumpFactor = newJumpFactor;
    emit jumpFactorChanged(jumpFactor);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton) {
        QPointF pos = event->scenePos();

        RigidBody *rb = new RigidBody();
        addItem(rb);

        rb->setPos(rb->mapFromScene(pos));
        rb->setFlags(QGraphicsItem::ItemIsMovable);
    }
    QGraphicsScene::mousePressEvent(event);
}

bool Scene::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);
    if(event->type() == QEvent::KeyPress) {
        if(((QKeyEvent*)event)->isAutoRepeat()) {
            return false;
        }
        int key = ((QKeyEvent*)event)->key();
        switch(key) {
        case Qt::Key_D:
            player->addDirection(1);
            checkTimer();
            break;
        case Qt::Key_Q:
            player->addDirection(-1);
            checkTimer();
            break;
        case Qt::Key_Space:
            if(fallTimer->isActive()) {
                return false;
            }
            else {
                if(jumpAnimation->state() == QAbstractAnimation::Stopped)
                jumpAnimation->start();
            }
            break;
        }
    }
    else if(event->type() == QEvent::KeyRelease) {
        if(((QKeyEvent*)event)->isAutoRepeat()) {
            return false;
        }
        int key = ((QKeyEvent*)event)->key();
        switch(key) {
        case Qt::Key_D:
            player->addDirection(-1);
            checkTimer();
            break;
        case Qt::Key_Q:
            player->addDirection(1);
            checkTimer();
            break;
        }
    }
    return false;
}

void Scene::movePlayer() {

//    if(player->isFalling()) {
//        return;
//    }

    int direction = player->getDirection();

    if(direction == 0) {
        return;
    }

    if(!player->isFalling()) {
        if(!(lastPlatform && player->isTouchingPlatform(lastPlatform)) && jumpAnimation->state() == QAbstractAnimation::Stopped) {
            if(lastPlatform) {
                player->fall();
                fallTimer->start();
            }
        }
    }

    const int dx = direction * velocity;

    // Si il va à droite
    if(direction > 0) {

        // On bloque tout mouvement au delà de 7950
        if(player->pos().x() > 7950) {
            return;
        }

        // On déplace le joueur
        player->moveBy(dx, 0);

        // Différence de position entre le scroll et le joueur
        int diff = player->pos().x() - scroll->value();

        // Si le joueur est à 800 pixels de la gauche de l'écran, on bouge l'écran
        if(diff > 800) {

            // (sauf si l'écran est déjà trop à droite)
            if(scroll->value() > 6720) {
                return;
            }

            scroll->setValue(scroll->value() + dx);
            // [!] Ici, déplacer aussi tous les éléments de l'UI de dx
        }
    }
    // Tout pareil mais à gauche
    if(direction < 0) {
        if(player->pos().x() < 50) {
            return;
        }
        player->moveBy(dx, 0);
        int diff = player->pos().x() - scroll->value();
        if(diff < 480) {
            if(scroll->value() < 100) {
                return;
            }
            scroll->setValue(scroll->value() + dx);
            // Ici, déplacer aussi tous les éléments de l'UI de dx
        }
    }



    return;
}

void Scene::jumpPlayer() {

    if(jumpAnimation->state() == QAbstractAnimation::Stopped) {
        qDebug() << "animation finie, on stop";
        player->stand();
        return;
    }

    QGraphicsItem *item = collidingPlatforms();
    if(item) {
        if(player->isTouchingHead(item)) {

            qDebug() << "head touched";

            jumpAnimation->stop();

            if(lastPlatform) {
                player->setPos(player->pos().x(), lastPlatform->pos().y() - player->boundingRect().height());
                return;
            }
            if(!lastPlatform) {
                player->setPos(player->pos().x(), groundLevel - player->boundingRect().height());
                return;
            }
        }
        else {
            if(handleCollisionWithPlatform()) {
                qDebug() << "platform touched";
                return;
            }
        }
    }

    if(fallTimer->isActive()) {
        return;
    }
    qreal y = (groundLevel - player->boundingRect().height()) - jumpAnimation->currentValue().toReal() * jumpHeight;
    if(lastPlatform) {
        qDebug() << "last platform = " << lastPlatform;
        y = (lastPlatform->pos().y() - player->boundingRect().height()) - jumpAnimation->currentValue().toReal() * jumpHeight;
        if(!(lastPlatform && player->isTouchingPlatform(lastPlatform)) && jumpFactor < 0.1) {
            if((player->pos().x() < lastPlatform->pos().x()) || (player->pos().x() > lastPlatform->pos().x() + lastPlatform->boundingRect().width())) {
                if(!lastPlatform) {
                    lastPlatform = 0;
                }
                if(player->pos().y() < groundLevel) {
                    player->fall();
                    fallTimer->start();
                    return;
                }
            }
        }
    }
    player->setPos(player->pos().x(), y);
}

void Scene::fallPlayer() {
    qDebug() << "fall";
    player->setPos(player->pos().x(), player->pos().y() + 20);
    QGraphicsItem *item = collidingPlatforms();
    if(item && handleCollisionWithPlatform()) {
        fallTimer->stop();
        player->walk();
    }
        else if(player->pos().y() + player->boundingRect().height() >= groundLevel) {
            player->setPos(player->pos().x(), groundLevel - player->boundingRect().height());
            fallTimer->stop();
            player->walk();
            lastPlatform = 0;
        }
}

void Scene::checkTimer() {
    if(player->getDirection() == 0) {
        player->stand();
        moveTimer->stop();
    }
    else if(!moveTimer->isActive()) {
        moveTimer->start();
        player->walk();
    }
}

QGraphicsItem * Scene::collidingPlatforms() {
    QList<QGraphicsItem*> items = collidingItems(player);
    foreach(QGraphicsItem *item, items) {
        if(RigidBody *rigidbody = qgraphicsitem_cast<RigidBody *>(item)) {
            return rigidbody;
        }
    }
    return 0;
}

void Scene::jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{
    if(newState == QAbstractAnimation::Stopped && oldState == QAbstractAnimation::Running) {
//         handleCollisionWithPlatform(); //??
    }
}

bool Scene::handleCollisionWithPlatform() {
    QGraphicsItem * platform = collidingPlatforms();
    if(platform) {
        QPointF platformPos = platform->pos();
        if(player->isTouchingFoot(platform)) {
            player->setPos(player->pos().x(), platformPos.y() - player->boundingRect().height());
            lastPlatform = platform;
            jumpAnimation->stop();
            return true;
        }
    }
    else {
        lastPlatform = 0;
    }
    return false;
}

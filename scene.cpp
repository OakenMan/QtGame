#include "scene.h"

#include <QDebug>
#include <QPointF>

#include "rigidbody.h"
#include "rbodytype.h"

#include "entities/coingold.h"

Scene::Scene(QScrollBar *s, QObject *parent):QGraphicsScene(0, 0, 8000, 720, parent)
{
    scroll = s;
    velocity = 7;
    jumpHeight = 144;
    groundLevel = 672;

    // Description de l'animation de saut
    jumpAnimation = new QPropertyAnimation(this);
    jumpAnimation->setTargetObject(this);
    jumpAnimation->setPropertyName("jumpFactor");
    jumpAnimation->setStartValue(0);
    jumpAnimation->setKeyValueAt(0.5, 1);
    jumpAnimation->setEndValue(0);
    jumpAnimation->setDuration(700);
    jumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);

    connect(this, &Scene::jumpFactorChanged, this, &Scene::jumpPlayer);
    //    connect(jumpAnimation, &QPropertyAnimation::stateChanged, this, &Scene::jumpStatusChanged);

    // Timer pour le mouvement
    moveTimer = new QTimer(this);
    moveTimer->setTimerType(Qt::PreciseTimer);
    moveTimer->setInterval(20); // <--- durée d'une frame en ms (donc fps ~= 1000/20 = 50)
    connect(moveTimer, &QTimer::timeout, this, &Scene::movePlayer);

    // Timer pour la chute
    fallTimer = new QTimer(this);
    fallTimer->setInterval(20); // <--- durée d'une frame en ms
    moveTimer->setTimerType(Qt::PreciseTimer);
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

    // Gestion du son dans la scène
    soundManager = new SoundManager();
    //    connect(this, &Scene::playSound, soundManager, &SoundManager::playSoundEffect);
    //    emit playSound(mLevel1);

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

/**
 * @brief Event déclanché à chaque clic de souris (actuellement utilisé pour placer des blocs, à supprimer plus tard)
 */
void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton) {
        QPointF pos = event->scenePos();
        QPointF newPos(((int)pos.x() / 48) * 48, ((int)pos.y() / 48) * 48);

        RigidBody *rb = new RigidBody();
        addItem(rb);

        rb->setPos(rb->mapFromScene(newPos));
        rb->setFlags(QGraphicsItem::ItemIsMovable);
    }
    QGraphicsScene::mousePressEvent(event);
}

/**
 * @brief Filtre d'évenements. Récupère les touches pressées et relachées pour gérer les mouvements du joueur
 */
bool Scene::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);

    // Si une touche est pressée
    if(event->type() == QEvent::KeyPress) {
        if(((QKeyEvent*)event)->isAutoRepeat()) {   // On ignore les event à part le tout premier
            return false;
        }
        int key = ((QKeyEvent*)event)->key();
        switch(key) {
        case Qt::Key_D:                     // Droite
            player->addDirection(1);
            checkTimer();
            break;
        case Qt::Key_Q:                     // Gauche
            player->addDirection(-1);
            checkTimer();
            break;
        case Qt::Key_Space:                 // Saut
            if(fallTimer->isActive()) {     // On ne peut pas sauter si on tombe
                return false;
            }
            else {
                if(jumpAnimation->state() == QAbstractAnimation::Stopped) {
                    soundManager->playSoundEffect(sJump);
                    jumpAnimation->start();
                    player->jump();
                }
            }
            break;
        }
    }
    // Si une touche est relachée, on stop le mouvement
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

/**
 * @brief Fonction appelée par le timer 'moveTimer' lorsque le joueur est en mouvement
 */
void Scene::movePlayer() {

    // Dé-commenter pour interdire le mouvement en chute libre
    //    if(player->isFalling()) {
    //        return;
    //    }

    checkCollidingCoins();

    int direction = player->getDirection();

    if(direction == 0) {
        return;
    }

    // Si le joueur n'est pas en train de tomber
    if(!player->isFalling()) {
        // Qu'il ne touche aucune plateforme et qu'il n'est pas en train de sauter
        if(!(lastPlatform && player->isTouchingPlatform(lastPlatform)) && jumpAnimation->state() == QAbstractAnimation::Stopped) {
            if(lastPlatform) {
                // Alors il tombe
                player->fall();
                fallTimer->start();
            }
        }
    }

    const int dx = direction * velocity;

    player->nextFrame();

    // Si il va à droite
    if(direction > 0 && canMoveRight()) {

        // On bloque tout mouvement au delà de 7950 (frontière droite)
        if(player->pos().x() >= 8000) {
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
    if(direction < 0 && canMoveLeft()) {
        if(player->pos().x() <= 0) {
            return;
        }
        player->moveBy(dx, 0);
        int diff = player->pos().x() - scroll->value();
        if(diff < 480) {
            if(scroll->value() < 0) {
                return;
            }
            scroll->setValue(scroll->value() + dx);
            // [!] Ici, déplacer aussi tous les éléments de l'UI de dx
        }
    }

    return;
}

/**
 * Fonction appelée lorsque le 'jumpfactor' change, donc au fur et à mesure que l'animation de jump évolue
 */
void Scene::jumpPlayer() {

    checkCollidingCoins();

    // Si l'animation est finie, on s'arrête là
    if(jumpAnimation->state() == QAbstractAnimation::Stopped) {
        player->stand();
        return;
    }

    // Si le joueur touchr une plateforme
    QGraphicsItem *item = collidingPlatforms();
    if(item) {
        // Avec la tête...
        if(!canMoveUp()) {

            jumpAnimation->stop();  // On stoppe l'animation
            player->fall();         // Et on le fait retomber
            fallTimer->start();
        }
        // Avec ses pieds...

        // Si il touche une plateforme, on arrête la chute
        else if(!canMoveDown()) {
            jumpAnimation->stop();
            player->stand();

            QRectF itemRect = item->mapRectToScene(item->boundingRect());

            QPointF finalPos(player->pos().x(), itemRect.y() - player->boundingRect().height());
            lastPlatform = item;

            player->setPos(finalPos);
            return;
        }

    }

    if(fallTimer->isActive()) {
        return;
    }

    // y = future position Y du joueur
    qreal y = (groundLevel - player->boundingRect().height()) - jumpAnimation->currentValue().toReal() * jumpHeight;
    if(lastPlatform) {
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

    // On met à jour la position du joueur
    player->setPos(player->pos().x(), y);
}


/**
 * Fonction appelée par le timer 'fallTimer', lorsque le joueur est en train de tomber
 */
void Scene::fallPlayer() {

    checkCollidingCoins();

    // On met à jour la position du joueur
    player->setPos(player->pos().x(), player->pos().y() + 15);

    QGraphicsItem *item = collidingPlatforms();

    // Si il touche une plateforme, on arrête la chute
    if(!canMoveDown()) {
        fallTimer->stop();
        player->stand();

        QRectF itemRect = item->mapRectToScene(item->boundingRect());

        QPointF finalPos(player->pos().x(), itemRect.y() - player->boundingRect().height());
        lastPlatform = item;

        player->setPos(finalPos);
    }
}

/**
 * Fonction appelée à chaque input, pour vérifier si le joueur est encore en mouvement ou pas
 */
void Scene::checkTimer() {
    // Si il ne bouge pas, on arrête le timer
    if(player->getDirection() == 0) {
        player->stand();
        moveTimer->stop();
    }
    // Si le timer était éteind, on le redémarre
    else if(!moveTimer->isActive()) {
        moveTimer->start();
        player->walk();
    }
}

/**
 * @brief Renvoie le RigidBody touché par le joueur, ou nullptr si le joueur ne touche rien
 */
QGraphicsItem * Scene::collidingPlatforms() {
    QList<QGraphicsItem*> items = collidingItems(player);
    foreach(QGraphicsItem *item, items) {
        if(RigidBody *rigidbody = qgraphicsitem_cast<RigidBody *>(item)) {
            return rigidbody;
        }
    }
    return nullptr;
}

void Scene::checkCollidingCoins()
{
    QList<QGraphicsItem*> items = collidingItems(player);
    for(QGraphicsItem *item : items) {
        RigidBody* rb = qgraphicsitem_cast<RigidBody*>(item);
        RBodyType type = rb->getType();
        if(type == iCoinGold) {
            removeItem(rb);
            soundManager->playSoundEffect(sCoin);
        }
        else if(type == tWater || type == tLava) {
            qDebug() << "game over";
            soundManager->playSoundEffect(sGameover);
            setForegroundBrush(QColor(0, 0, 0, 127));
        }
    }
}

/**
 * Renvoie true si le joueur peut aller à droite, false si il est bloqué
 */
bool Scene::canMoveRight()
{
    QRectF playerRect = player->mapRectToScene(player->boundingRect());

    QList<QGraphicsItem*> items = collidingItems(player);
    for(QGraphicsItem *item : items) {
        RigidBody* rb = qgraphicsitem_cast<RigidBody*>(item);
        if(rb->isSolid()) {
            QRectF itemRect = rb->mapRectToScene(rb->boundingRect());
            if(playerRect.right() <= itemRect.right()) {
                return false;
            }
        }
    }

    return true;
}

/**
 * Renvoie true si le joueur peut aller à gauche, false si il est bloqué
 */
bool Scene::canMoveLeft()
{
    QRectF playerRect = player->mapRectToScene(player->boundingRect());

    QList<QGraphicsItem*> items = collidingItems(player);
    for(QGraphicsItem *item : items) {
        RigidBody* rb = qgraphicsitem_cast<RigidBody*>(item);
        if(rb->isSolid()) {
            QRectF itemRect = rb->mapRectToScene(rb->boundingRect());
            if(playerRect.left() >= itemRect.left()) {
                return false;
            }
        }
    }

    return true;
}

/**
 * Renvoie true si le joueur peut aller en haut, false si il est bloqué
 */
bool Scene::canMoveUp()
{
    QRectF playerRect = player->mapRectToScene(player->boundingRect());

    QList<QGraphicsItem*> items = collidingItems(player);
    for(QGraphicsItem *item : items) {
        RigidBody* rb = qgraphicsitem_cast<RigidBody*>(item);
        if(rb->isSolid()) {
            QRectF itemRect = rb->mapRectToScene(rb->boundingRect());
            // Si le haut du joueur est en dessous du bas de la plateforme
            if(playerRect.top() >= itemRect.bottom()-10) {
                // Si la plateforme est au dessus du joueur (et pas sur les côtés)
                if(itemRect.center().x() >= playerRect.left() && itemRect.center().x() <= playerRect.right()) {
                    return false;
                }
            }
        }
    }

    return true;
}

/**
 * Renvoie true si le joueur peut aller en bas, false si il est bloqué
 */
bool Scene::canMoveDown()
{
    QRectF playerRect = player->mapRectToScene(player->boundingRect());

    QList<QGraphicsItem*> items = collidingItems(player);
    for(QGraphicsItem *item : items) {
        RigidBody* rb = qgraphicsitem_cast<RigidBody*>(item);
        if(rb->isSolid()) {
            QRectF itemRect = rb->mapRectToScene(rb->boundingRect());
            // Si le bas du joueur est au dessus du haut de la plateforme
            if(playerRect.bottom() <= itemRect.top()+24) {
                // Si la plateforme est au dessus du joueur (et pas sur les côtés)
                if(itemRect.center().x() >= playerRect.left() && itemRect.center().x() <= playerRect.right()) {
                    return false;
                }
            }
        }
    }

    return true;
}

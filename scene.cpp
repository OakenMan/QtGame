#include "scene.h"

#include <QDebug>
#include <QPointF>

#include "rigidbody.h"

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
    connect(jumpAnimation, &QPropertyAnimation::stateChanged, this, &Scene::jumpStatusChanged);

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

        RigidBody *rb = new RigidBody();
        addItem(rb);

        rb->setPos(rb->mapFromScene(pos));
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
                if(jumpAnimation->state() == QAbstractAnimation::Stopped)
                    jumpAnimation->start();
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

    // Si il va à droite
    if(direction > 0) {

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
    if(direction < 0) {
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

    // Si l'animation est finie, on s'arrête là
    if(jumpAnimation->state() == QAbstractAnimation::Stopped) {
        player->stand();
        return;
    }

    // Si le joueur touchr une plateforme
    QGraphicsItem *item = collidingPlatforms();
    if(item) {
        // Avec la tête...
        if(player->isTouchingHead(item)) {

            jumpAnimation->stop();  // On stoppe l'animation (TODO: le faire redescendre plus doucement ?)

            // Puis on le fait retomber sur sa dernière plateforme
            if(lastPlatform) {
                player->setPos(player->pos().x(), lastPlatform->pos().y() - player->boundingRect().height());
                return;
            }
            // Ou le sol
            if(!lastPlatform) {
                player->setPos(player->pos().x(), groundLevel - player->boundingRect().height());
                return;
            }
        }
        // Avec ses pieds...
        else {
            if(handleCollisionWithPlatform()) {
                return; // On s'arrête là
            }
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
    // On met à jour la position du joueur (TODO : gérer l'acceleration ?)
    player->setPos(player->pos().x(), player->pos().y() + 20);

    QGraphicsItem *item = collidingPlatforms();

    // Si il touche une plateforme, on arrête la chute
    if(item && handleCollisionWithPlatform()) {
        fallTimer->stop();
        player->walk();
    }
    // Si il arrive au sol, on arrête la chute
    else if(player->pos().y() + player->boundingRect().height() >= groundLevel) {
        player->setPos(player->pos().x(), groundLevel - player->boundingRect().height());
        fallTimer->stop();
        player->walk();
        lastPlatform = 0;
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
 * @brief Renvoie le RigidBody touché par le joueur
 */
QGraphicsItem * Scene::collidingPlatforms() {
    QList<QGraphicsItem*> items = collidingItems(player);
    foreach(QGraphicsItem *item, items) {
        if(RigidBody *rigidbody = qgraphicsitem_cast<RigidBody *>(item)) {
            return rigidbody;
        }
//        if(AutreObjet *other = qgraphicsitem_cast<AutreObjet *>(item)) {
//            return other;
//        }
    }
    return 0;
}

// ça maybe on s'en tape
void Scene::jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{
    if(newState == QAbstractAnimation::Stopped && oldState == QAbstractAnimation::Running) {
        //         handleCollisionWithPlatform(); //??
    }
}

/**
 * Gère les collision avec les plateformes (verticales seulement)
 */
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

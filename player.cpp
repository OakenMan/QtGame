#include "player.h"

#include <QRectF>
#include <QPainter>
#include <QEvent>
#include <QKeyEvent>

#include <QDebug>

#include "physicsengine.h"
#include "soundmanager.h"
#include "interface.h"
#include "scene.h"

/**
 * Constructeur
 */
Player::Player():Entity()
{
    setFlags(QGraphicsItem::ItemClipsToShape);
    setFlags(QGraphicsItem::ItemIsFocusable);   // Pour recevoir les input clavier

    // Initialisation des pixmap
    standPixmap = QPixmap(":/player/ressources/Player/p1_stand.png");
    jumpPixmap = QPixmap(":/player/ressources/Player/p1_jump.png");
    hurtPixmap = QPixmap(":/player/ressources/Player/p1_hurt.png");

    walk1 = QPixmap(":/player/ressources/Player/p1_walk/PNG/p1_walk01.png");
    walk2 = QPixmap(":/player/ressources/Player/p1_walk/PNG/p1_walk02.png");
    walk3 = QPixmap(":/player/ressources/Player/p1_walk/PNG/p1_walk03.png");
    walk4 = QPixmap(":/player/ressources/Player/p1_walk/PNG/p1_walk04.png");
    walk5 = QPixmap(":/player/ressources/Player/p1_walk/PNG/p1_walk05.png");
    walk6 = QPixmap(":/player/ressources/Player/p1_walk/PNG/p1_walk06.png");
    walk7 = QPixmap(":/player/ressources/Player/p1_walk/PNG/p1_walk07.png");
    walk8 = QPixmap(":/player/ressources/Player/p1_walk/PNG/p1_walk08.png");
    walk9 = QPixmap(":/player/ressources/Player/p1_walk/PNG/p1_walk09.png");
    walk10 = QPixmap(":/player/ressources/Player/p1_walk/PNG/p1_walk10.png");
    walk11 = QPixmap(":/player/ressources/Player/p1_walk/PNG/p1_walk11.png");

    pixmap = standPixmap;

    setTransformOriginPoint(boundingRect().center());

    // Initialisation des variables
    direction = 0;
    state = Standing;
    walkFrame = 0;
    dead = false;

    health = 3;
    coins = 0;
    boxes = 0;

    // Description de l'animation de saut
    jumpAnimation = new QPropertyAnimation(this);
    jumpAnimation->setTargetObject(this);
    jumpAnimation->setPropertyName("jumpFactor");
    jumpAnimation->setStartValue(0);
    jumpAnimation->setKeyValueAt(0.5, 1);
    jumpAnimation->setEndValue(0);
    jumpAnimation->setDuration(700);
    jumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);
    connect(this, &Player::jumpFactorChanged, this, &Player::jumpPlayer);

    // Timer pour le mouvement
    moveTimer = new QTimer(this);
    moveTimer->setTimerType(Qt::PreciseTimer);
    moveTimer->setInterval(20); // <--- durée d'une frame en ms (donc fps ~= 1000/20 = 50)
    connect(moveTimer, &QTimer::timeout, this, &Player::movePlayer);

    // Timer pour la chute
    fallTimer = new QTimer(this);
    fallTimer->setInterval(20); // <--- durée d'une frame en ms
    fallTimer->setTimerType(Qt::PreciseTimer);
    connect(fallTimer, &QTimer::timeout, this, &Player::fallPlayer);

    // Pour l'afficher devant les items et la déco
    setZValue(1);
}

/**
 * Destructeur
 */
Player::~Player()
{

}

/*===== SURCHARGES DE MÉTHODES HÉRITÉES =====*/
QRectF Player::boundingRect() const {
    return QRectF(0, 0, DEFAULT_TILE_SIZE, 1.5*DEFAULT_TILE_SIZE);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    painter->drawPixmap(boundingRect().toRect(), pixmap);

    //    QRectF head(7, 0, boundingRect().width()-14, 5);
    //    QRectF foot(7, boundingRect().height(), boundingRect().width()-14, 5);
    //    QRectF body(boundingRect());

    //    QBrush brush1(Qt::blue);
    //    QBrush brush2(Qt::red);

    //    painter->fillRect(head, brush1);
    //    painter->fillRect(foot, brush1);

    //    RigidBody *rb = collidingPlatforms();
    //    if(rb) {
    //        painter->fillRect(foot, brush2);
    //    }

    //    painter->drawRect(head);
    //    painter->drawRect(foot);
    //    painter->drawRect(body);

    Q_UNUSED(widget);
    Q_UNUSED(options);
}

/*===== NOUVELLES MÉTHODES (GETTERS, SETTERS...) =====*/
int Player::getDirection() const {
    return direction;
}

void Player::addDirection(int newDirection) {
    if(direction == newDirection) {
        return;
    }

    direction += newDirection;
    checkTimer();

    // Changement de direction du sprite
    if(direction == -1) {
        setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
    }
    else if(direction == 1){
        setTransform(QTransform());
    }
}

void Player::stand() {
    state = Standing;
    pixmap = standPixmap;
    update(boundingRect());
}

void Player::jump() {
    if(fallTimer->isActive()) {     // On ne peut pas sauter si on tombe
        return;
    }
    else {
        if(jumpAnimation->state() == QAbstractAnimation::Stopped) {
            jumpAnimation->start();
            state = Jumping;
            pixmap = jumpPixmap;
            SoundManager::playSound(sJump);
        }
    }
}

void Player::walk() {
    //    if(state == Walking) {
    //        return;
    //    }
    //    state = Walking;
}

void Player::fall() {
    fallTimer->start();
    state = Falling;
    pixmap = hurtPixmap;
}

bool Player::isFalling() {
    return state == Falling;
}

/**
 * Change la frame d'animation de marche
 */
void Player::nextFrame()
{
    if(state==Falling || state==Jumping) {
        return;
    }

    walkFrame++;

    if(walkFrame >= 12) {
        walkFrame = 1;
    }

    switch(walkFrame) {
    case 1: pixmap = walk1; break;
    case 2: pixmap = walk2; break;
    case 3: pixmap = walk3; break;
    case 4: pixmap = walk4; break;
    case 5: pixmap = walk5; break;
    case 6: pixmap = walk6; break;
    case 7: pixmap = walk7; break;
    case 8: pixmap = walk8; break;
    case 9: pixmap = walk9; break;
    case 10: pixmap = walk10; break;
    case 11: pixmap = walk11; break;
    }
}

int Player::getHealth() {
    return health;
}

int Player::getCoins() {
    return coins;
}

int Player::getBoxes() {
    return boxes;
}

void Player::setBoxes(int boxes)
{
    this->boxes = boxes;
}

/*===== GESTION DES DÉPLACEMENTS DU JOUEUR =====*/
qreal Player::getJumpFactor() const
{
    return jumpFactor;
}

void Player::setJumpFactor(const qreal &newJumpFactor)
{
    if(jumpFactor == newJumpFactor) {
        return;
    }

    jumpFactor = newJumpFactor;
    emit jumpFactorChanged(jumpFactor);
}

void Player::setLastPlatform(QGraphicsItem *item)
{
    lastPlatform = item;
}

void Player::movePlayer() {

    checkCollisions();

    if(direction == 0) {
        return;
    }

    // Si le joueur n'est pas en train de tomber ou sauter
    if(!isFalling() && jumpAnimation->state() == QAbstractAnimation::Stopped) {
        //         Qu'il ne touche aucune plateforme et qu'il n'est pas en train de sauter
        if(!(lastPlatform && isTouchingPlatform(lastPlatform)) && jumpAnimation->state() == QAbstractAnimation::Stopped) {
            if(lastPlatform) {
                // Alors il tombe
                fall();
            }
        }
    }

    const int dx = direction * velocity;

    nextFrame();

    // Si il va à droite
    if(direction > 0 && PhysicsEngine::canMoveRight(this, false)) {

        if(pos().x() >= 8000) {
            return;
        }

        moveBy(dx, 0);
        emit playerMoved(dx);
    }
    // Si il va à gauche
    if(direction < 0 && PhysicsEngine::canMoveLeft(this, false)) {

        if(pos().x() <= 0) {
            return;
        }

        moveBy(dx, 0);
        emit playerMoved(dx);
    }

    return;
}

void Player::jumpPlayer() {

    checkCollisions();

    // Si l'animation est finie, on s'arrête là
    if(jumpAnimation->state() == QAbstractAnimation::Stopped) {
        stand();
        return;
    }

    // Si le joueur touche une plateforme
    RigidBody *item = collidingPlatforms();

    if(item) {
        // Avec la tête ---> on le fait tomber
        if(isTouchingHead(item)) {
            jumpAnimation->stop();
            fall();
            return;
        }
        // Avec les pieds ---> on arrête la chute
        else if(isTouchingFoot(item)) {
            jumpAnimation->stop();
            stand();

            QRectF itemRect = item->mapRectToScene(item->boundingRect());
            QPointF finalPos(pos().x(), itemRect.y() - boundingRect().height());
            lastPlatform = item;
            setPos(finalPos);
            return;
        }
    }

    if(fallTimer->isActive()) {
        return;
    }

    // y = future position Y du joueur
    qreal y = (groundLevel - boundingRect().height()) - jumpAnimation->currentValue().toReal() * jumpHeight;
    if(lastPlatform) {
        y = (lastPlatform->pos().y() - boundingRect().height()) - jumpAnimation->currentValue().toReal() * jumpHeight;
        if(!(lastPlatform && isTouchingPlatform(lastPlatform)) && jumpFactor < 0.1) {
            if((pos().x() < lastPlatform->pos().x()) || (pos().x() > lastPlatform->pos().x() + lastPlatform->boundingRect().width())) {
                if(!lastPlatform) {
                    lastPlatform = 0;
                }
                if(pos().y() < groundLevel) {
                    fall();
                    return;
                }
            }
        }
    }

    // On met à jour la position du joueur
    setPos(pos().x(), y);
}

void Player::fallPlayer() {

    checkCollisions();

    // On met à jour la position du joueur
    setPos(pos().x(), pos().y() + 15);

    RigidBody *item = collidingPlatforms();

    // Si il touche une plateforme, on arrête la chute
    if(item) {
        if(isTouchingFoot(item)) {
            fallTimer->stop();
            stand();

            QRectF itemRect = item->mapRectToScene(item->boundingRect());
            QPointF finalPos(pos().x(), itemRect.y() - boundingRect().height());
            lastPlatform = item;
            setPos(finalPos);
        }
    }

    if(pos().y() > 720) {
        die();
    }
}

void Player::checkTimer() {
    // Si il ne bouge pas, on arrête le timer
    if(direction == 0) {
        moveTimer->stop();
        stand();
    }
    // Si le timer était éteind, on le redémarre
    else if(!moveTimer->isActive()) {
        moveTimer->start();
        walk();
    }
}

/*===== DETECTION DES COLLISIONS (+ précis qu'avec le PhysicsEngine...) =====*/
RigidBody * Player::collidingPlatforms() {
    RigidBody *rb = nullptr;

    QList<QGraphicsItem*> items = collidingItems();
    foreach(QGraphicsItem *item, items) {
        if(RigidBody *rigidbody = qgraphicsitem_cast<RigidBody *>(item)) {
            if(rigidbody->isSolid()) {
                // On retourne en priorité les objets qui touche les pieds
                if(isTouchingFoot(rigidbody)) {
                    return rigidbody;
                }
                // Ou ceux qui touchent la tête
                else if(isTouchingHead(rigidbody)) {
                    return rigidbody;
                }
                // Puis les autres
                else {
                    rb = rigidbody;
                }
            }
        }
    }

    return rb;
}

void Player::checkCollisions()
{
    QList<QGraphicsItem*> items = collidingItems();

    for(QGraphicsItem *item : items) {
        RigidBody* rb = qgraphicsitem_cast<RigidBody*>(item);
        RBodyType type = rb->getType();

        // Si c'est une pièce
        if(type == iCoinGold) {
            delete rb;
            SoundManager::playSound(sCoin);
            coins++;
            emit statsChanged();
        }

        // Si c'est de l'eau ou de la lave
        else if(type == tWater || type == tLava) {
            die();
        }

        // Si c'est un mob
        else if(rb->type() == UserType + 5) {
            // Mais qu'on lui saute dessus
            if(isTouchingFoot(rb)) {
                delete rb;
            }
            // Sinon
            else {
                delete rb;
                health--;
                if(health == 0) {
                    die();
                }
                emit statsChanged();
            }
        }
        else if(type == tBox) {
            if(isTouchingHead(rb) && jumpAnimation->state() != QAbstractAnimation::Stopped) {
                QTimer::singleShot(100, rb, SLOT(breakBox()));
                boxes++;
                emit statsChanged();
            }
        }
        else if(type == tBoxItem || type == tBoxCoin) {
            if(isTouchingHead(rb) && jumpAnimation->state() != QAbstractAnimation::Stopped) {
                QTimer::singleShot(100, rb, SLOT(breakBox()));
            }
        }
    }
}

void Player::die()
{
    if(dead) {
        return;
    }
    dead = true;
    pixmap = hurtPixmap;
    QTimer::singleShot(500, Qt::PreciseTimer, this->scene(), SLOT(gameover()));
}

bool Player::isTouchingFoot(QGraphicsItem *item){
    QRectF rect(pos().x()+7, (pos().y() + boundingRect().height()), boundingRect().width()-14, 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());

    return rect.intersects(otherRect);
}

bool Player::isTouchingHead(QGraphicsItem *item){
    QRectF rect(pos().x()+7, pos().y(), boundingRect().width()-14, 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());

    return rect.intersects(otherRect);
}

bool Player::isTouchingPlatform(QGraphicsItem *item){

    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 5, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());

    return rect.intersects(otherRect);
}

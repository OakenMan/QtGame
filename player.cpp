#include "player.h"

#include <QRectF>

#include <QDebug>
#include <QPainter>

Player::Player()
{
    setFlags(QGraphicsItem::ItemClipsToShape);

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

    direction = 0;
    state = Standing;
    walkFrame = 0;

    // Pour l'afficher devant les items et la déco
    setZValue(1);
}

Player::~Player()
{

}

// Le joueur fait 1 bloc de large et 1 bloc et demi de haut
QRectF Player::boundingRect() const {
    return QRectF(0, 0, DEFAULT_TILE_SIZE, 1.5*DEFAULT_TILE_SIZE);
}

void Player::stand() {
    state = Standing;
    pixmap = standPixmap;
}

void Player::jump() {
    state = Jumping;
    pixmap = jumpPixmap;
}

void Player::walk() {
    if(state == Walking) {
        return;
    }
    state = Walking;
}

void Player::fall() {
    state = Falling;
    pixmap = hurtPixmap;
}

bool Player::isFalling() {
    return state == Falling;
}

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

int Player::getDirection() const {
    return direction;
}

void Player::addDirection(int newDirection) {
    if(direction == newDirection) {
        return;
    }

    direction += newDirection;

    setTransformOriginPoint(boundingRect().center());

    if(direction == -1) {
        setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
    }
    else if(direction == 1){
        setTransform(QTransform());
    }
}

bool Player::isTouchingFoot(QGraphicsItem *item){
    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) -5, boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());

    return rect.intersects(otherRect);
}

bool Player::isTouchingHead(QGraphicsItem *item){
    QRectF rect(pos().x(), pos().y(), boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());

    return rect.intersects(otherRect);
}

bool Player::isTouchingPlatform(QGraphicsItem *item){

    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 5, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());

    return rect.intersects(otherRect);
}

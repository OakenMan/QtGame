#include "player.h"

#include <QRectF>
#include <QBrush>
#include <QPainter>

Player::Player()
{
    setFlags(QGraphicsItem::ItemClipsToShape);
    direction = 0;
    state = Standing;
}

Player::~Player()
{

}

void Player::stand() {
    state = Standing;
}

void Player::jump() {
    state = Jumping;
}

void Player::walk() {
    if(state == Walking) {
        return;
    }
    state = Walking;
}

void Player::fall() {
    state = Falling;
}

bool Player::isFalling() {
    return state == Falling;
}

int Player::getDirection() const {
    return direction;
}

void Player::addDirection(int newDirection) {
    if(direction == newDirection) {
        return;
    }
    direction += newDirection;
}

QRectF Player::boundingRect() const {
    return QRectF(0, 0, 50, 100);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);

    painter->fillRect(rec, brush);
    painter->drawRect(rec);

    Q_UNUSED(widget);
    Q_UNUSED(options);
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

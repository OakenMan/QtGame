#include "player.h"

#include <QRectF>
#include <QDebug>

Player::Player()
{
    setFlags(QGraphicsItem::ItemClipsToShape);

    standPixmap = QPixmap(":/player/ressources/Player/p1_stand.png");
    walkPixmap = QPixmap(":/player/ressources/Player/p1_walk/PNG/p1_walk03.png");
    jumpPixmap = QPixmap(":/player/ressources/Player/p1_jump.png");
    hurtPixmap = QPixmap(":/player/ressources/Player/p1_hurt.png");

    pixmap = standPixmap;

    direction = 0;
    state = Standing;
}

Player::~Player()
{

}

QRectF Player::boundingRect() const {
    return QRectF(0, 0, 48, 72);
}

//void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {
//    QRectF rec = boundingRect();
//    QBrush brush(Qt::blue);

//    painter->fillRect(rec, brush);
//    painter->drawRect(rec);

//    Q_UNUSED(widget);
//    Q_UNUSED(options);
//}

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
    pixmap = walkPixmap;
}

void Player::fall() {
    state = Falling;
    pixmap = hurtPixmap;
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

    setTransformOriginPoint(boundingRect().center());

    if(direction == -1) {
        qDebug() << "direction = -1, on retourne";
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

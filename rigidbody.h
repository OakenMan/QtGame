#ifndef BRICK_H
#define BRICK_H

#include <QGraphicsItem>

class RigidBody : public QGraphicsItem
{
public:
    RigidBody();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);
};

#endif // BRICK_H

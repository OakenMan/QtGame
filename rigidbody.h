#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <QGraphicsItem>

class RigidBody : public QGraphicsItem
{
public:
    RigidBody();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

protected:
    QPixmap pixmap;
};

#endif // RIGIDBODY_H

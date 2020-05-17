#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <QGraphicsItem>

class RigidBody : public QGraphicsItem
{
public:
    RigidBody();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);
    int type() const override { return UserType + 1; }

protected:
    QPixmap pixmap;
};

#endif // RIGIDBODY_H

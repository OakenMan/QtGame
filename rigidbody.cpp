#include "rigidbody.h"

#include <QBrush>
#include <QPainter>

RigidBody::RigidBody()
{

}

QRectF RigidBody::boundingRect() const
{
    return QRectF(0, 0, 100, 100);
}

void RigidBody::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::gray);

    painter->fillRect(rec, brush);
    painter->drawRect(rec);

    Q_UNUSED(widget);
    Q_UNUSED(options);
}

#include "rigidbody.h"

#include <QPainter>

RigidBody::RigidBody()
{
    isSolid = true;
}

QRectF RigidBody::boundingRect() const
{
    return QRectF(0, 0, DEFAULT_TILE_SIZE, DEFAULT_TILE_SIZE);
}

void RigidBody::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    painter->drawPixmap(boundingRect().toRect(), pixmap);

    Q_UNUSED(widget);
    Q_UNUSED(options);
}

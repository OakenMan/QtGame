#include "brick.h"

#include <QPainter>
#include <QPixmap>

Brick::Brick()
{
    pixmap = QPixmap(":/images/textures/ground_brick.png");
}

void Brick::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    painter->drawPixmap(0, 0, 48, 48, pixmap);

    Q_UNUSED(widget);
    Q_UNUSED(options);
}

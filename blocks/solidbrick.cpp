#include "solidbrick.h"

#include <QPainter>
#include <QPixmap>

SolidBrick::SolidBrick()
{
    pixmap = QPixmap(":/images/textures/solid_brick.png");
}

void SolidBrick::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    painter->drawPixmap(0, 0, 48, 48, pixmap);

    Q_UNUSED(widget);
    Q_UNUSED(options);
}

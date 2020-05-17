#include "platformbrick.h"

#include <QPainter>
#include <QPixmap>

PlatformBrick::PlatformBrick()
{
    pixmap = QPixmap(":/images/textures/platform_brick.png");
}

void PlatformBrick::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    painter->drawPixmap(0, 0, 48, 48, pixmap);

    Q_UNUSED(widget);
    Q_UNUSED(options);
}

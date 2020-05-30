#include "boxprops.h"

#include <QPainter>

BoxProps::BoxProps()
{
    bodyType = iBoxProps;

    pixmap = QPixmap(":/tiles/ressources/Tiles/box.png");
}

void BoxProps::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    QPointF pos(boundingRect().top()+12, boundingRect().left()+12);
    painter->drawPixmap(pos.x(), pos.y(), 24, 24, pixmap);

    Q_UNUSED(widget);
    Q_UNUSED(options);
}

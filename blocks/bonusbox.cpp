#include "bonusbox.h"

#include <QPainter>
#include <QPixmap>

BonusBox::BonusBox()
{
    pixmap = QPixmap(":/images/textures/bonus_box.png");
}

void BonusBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    painter->drawPixmap(0, 0, 48, 48, pixmap);

    Q_UNUSED(widget);
    Q_UNUSED(options);
}

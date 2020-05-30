#include "boxitem.h"

#include <QGraphicsScene>

#include "entities/boxprops.h"
#include "entities/mushroom.h"
#include "entities/coingold.h"

BoxItem::BoxItem():Tile()
{
    bodyType = tBoxItem;

    pixmap = QPixmap(":/tiles/ressources/Tiles/boxItem.png");
}

void BoxItem::breakBox()
{
    if(!empty) {
        RigidBody *rb;

        int r = rand() % 3;
        switch (r) {
        case 0: rb = new BoxProps(); break;
        case 1: rb = new Mushroom(); break;
        case 2: rb = new CoinGold(); break;
        default:                     break;
        }

        scene()->addItem(rb);
        rb->setPos(QPointF(pos().x(), pos().y()-48));

        pixmap = QPixmap(":/tiles/ressources/Tiles/boxItem_disabled.png");

        update(QRectF(pos().x()-48, pos().y()-48, 144, 96));

        empty = true;
    }
}

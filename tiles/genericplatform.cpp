#include "genericplatform.h"

#include <QPainter>
#include <QGraphicsScene>

GenericPlatform::GenericPlatform():Tile()
{

}

void GenericPlatform::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    updatePixmap();

    painter->drawPixmap(boundingRect().toRect(), pixmap);

    Q_UNUSED(widget);
    Q_UNUSED(options);
}

void GenericPlatform::updatePixmap()
{
    bool tileOnTop = false;
    bool tileOnRight = false;
    bool tileOnLeft = false;
    bool tileOnBottom = false;

    const int usertype = QGraphicsItem::UserType;
    QList<QGraphicsItem*> items;

    items = scene()->items(QPointF(pos().x()+24, pos().y()-24));
    if(!items.isEmpty()) {
        if(items.at(0)->type() == usertype+3) {
            tileOnTop = true;
        }
    }

    items = scene()->items(QPointF(pos().x()+72, pos().y()+24));
    if(!items.isEmpty()) {
        if(items.at(0)->type() == usertype+3) {
            tileOnRight = true;
        }
    }

    items = scene()->items(QPointF(pos().x()-24, pos().y()+24));
    if(!items.isEmpty()) {
        if(items.at(0)->type() == usertype+3) {
            tileOnLeft = true;
        }
    }

    items = scene()->items(QPointF(pos().x()+24, pos().y()+72));
    if(!items.isEmpty()) {
        if(items.at(0)->type() == usertype+3) {
            tileOnBottom = true;
        }
    }

    if(tileOnLeft && tileOnRight) {
        pixmap = mid;
    }
    else if(tileOnLeft) {
        pixmap = right;
    }
    else if(tileOnRight) {
        pixmap = left;
    }
    if(tileOnTop) {
        pixmap = center;
    }
    else if(tileOnBottom) {
//        pixmap = QPixmap(":/tiles/ressources/Tiles/grassMid");
    }
}


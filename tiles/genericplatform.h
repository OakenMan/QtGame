#ifndef GENERICPLATFORM_H
#define GENERICPLATFORM_H

#include "tile.h"

class GenericPlatform : public Tile
{
public:
    GenericPlatform();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);
    int type() const override { return UserType + 3; }

    void updatePixmap();

protected:
    QPixmap basic;
    QPixmap center;
    QPixmap mid;
    QPixmap left;
    QPixmap right;

};

#endif // GENERICPLATFORM_H

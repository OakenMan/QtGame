#ifndef BOXPROPS_H
#define BOXPROPS_H

#include "entity.h"

class BoxProps: public Entity
{
public:
    BoxProps();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);
};

#endif // BOXPROPS_H

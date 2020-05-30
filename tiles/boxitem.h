#ifndef BOXITEM_H
#define BOXITEM_H

#include "tile.h"

class BoxItem: public Tile
{
    Q_OBJECT

public:
    BoxItem();

public slots:
    void breakBox();

private:
    bool empty;
};

#endif // BOXITEM_H

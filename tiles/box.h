#ifndef BOX_H
#define BOX_H

#include "tile.h"

class Box: public Tile
{
    Q_OBJECT

public:
    Box();

public slots:
    void breakBox();
};

#endif // BOX_H

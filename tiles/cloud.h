#ifndef CLOUD_H
#define CLOUD_H

#include "tile.h"

class Cloud: public Tile
{
public:
    Cloud();

    QRectF boundingRect() const;
};

#endif // CLOUD_H

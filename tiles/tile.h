#ifndef TILE_H
#define TILE_H

#include "rigidbody.h"

class Tile : public RigidBody
{
public:
    Tile();

    int type() const override { return UserType + 2; }

};

#endif // TILE_H

#ifndef ENTITY_H
#define ENTITY_H

#include "rigidbody.h"

class Entity: public RigidBody
{
public:
    Entity();

    int type() const override { return UserType + 4; }
};

#endif // ENTITY_H

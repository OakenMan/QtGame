#ifndef COLLISION_H
#define COLLISION_H

#include "Physics/physicbody.h"

class Collision
{
public:
    Collision();
    bool AABBvsAABB(PhysicBody* A, PhysicBody* B);
    void initialize();
    void applyImpulse();
    void positionalCorrection();
    void infiniteMassCorrection();

private:
    struct Vector2
    {
      float x;
      float y;
    };

    PhysicBody* A;
    PhysicBody* B;
    float penetration;
    Vector2 normal;
};

#endif // COLLISION_H

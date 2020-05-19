#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "physicbody.h"
#include <QThread>

class PhysicsEngine: public QThread
{
public:
    PhysicsEngine();
    void run() override;
    void updatePhysics(float dt);
    void add(PhysicBody* body);
    void remove(PhysicBody* body);

private:
    QList<PhysicBody*> bodies;
};

#endif // PHYSICSENGINE_H

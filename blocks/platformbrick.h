#ifndef PLATFORMBRICK_H
#define PLATFORMBRICK_H

#include "rigidbody.h"

class PlatformBrick : public RigidBody
{
public:
    PlatformBrick();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);
};

#endif // PLATFORMBRICK_H

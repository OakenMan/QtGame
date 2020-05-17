#ifndef GROUNDBRICK_H
#define GROUNDBRICK_H

#include "rigidbody.h"

class GroundBrick : public RigidBody
{
public:
    GroundBrick();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);
    int type() const override { return UserType + 2; }
};

#endif // GROUNDBRICK_H

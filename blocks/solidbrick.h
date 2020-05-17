#ifndef SOLIDBRICK_H
#define SOLIDBRICK_H

#include "rigidbody.h"

class SolidBrick : public RigidBody
{
public:
    SolidBrick();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);
    int type() const override { return UserType + 3; }
};

#endif // SOLIDBRICK_H

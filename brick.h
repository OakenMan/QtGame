#ifndef BRICK_H
#define BRICK_H

#include "rigidbody.h"

class Brick : public RigidBody
{
public:
    Brick();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);
};

#endif // BRICK_H

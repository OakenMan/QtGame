#ifndef BONUSBOX_H
#define BONUSBOX_H

#include "rigidbody.h"

class BonusBox : public RigidBody
{
public:
    BonusBox();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);
    int type() const override { return UserType + 5; }
};

#endif // BONUSBOX_H

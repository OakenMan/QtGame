#ifndef PHYSICBODY_H
#define PHYSICBODY_H

#include "QGraphicsItem"
#include "QRectF"

class PhysicBody: public QGraphicsItem
{
public:
    PhysicBody();
    QRectF boundingRect() const override;
};

#endif // PHYSICBODY_H

#ifndef FLY_H
#define FLY_H

#include "genericmob.h"

class Fly: public GenericMob
{
public:
    Fly();

    QRectF boundingRect() const;

protected slots:
    void move();
    void updatePixmap();

private:
    QPixmap fly1;
    QPixmap fly2;
    QPixmap dead;

    int direction;
    int dist;
    int currentFrame;
};

#endif // FLY_H

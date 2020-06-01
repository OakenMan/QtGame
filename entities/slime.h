#ifndef SLIME_H
#define SLIME_H

#include "genericmob.h"

class Slime: public GenericMob
{
public:
    Slime();

    QRectF boundingRect() const;

protected slots:
    void move();
    void updatePixmap();

private:
    int direction;
    int currentFrame;

    QPixmap walk1;
    QPixmap walk2;
    QPixmap dead;

};

#endif // SLIME_H

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

private:
    QPixmap walk1;
    QPixmap walk2;
    QPixmap dead;

    int direction;
};

#endif // SLIME_H

#ifndef GENERICMOB_H
#define GENERICMOB_H

#include <QTimer>

#include "entity.h"

class GenericMob: public Entity
{
public:
    GenericMob();
    int type() const override { return UserType + 5; }
    void hasAI(bool b);

protected:
    QTimer * moveTimer;


};

#endif // GENERICMOB_H

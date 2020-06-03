#include "genericmob.h"

#include <QDebug>

GenericMob::GenericMob():Entity()
{
    // Timer pour le mouvement du mob
    moveTimer = new QTimer();
    moveTimer->setInterval(40); // <--- durée d'une frame en ms
    moveTimer->setTimerType(Qt::CoarseTimer);   //### repasser à PreciseTimer si les mobs "lagent" trop
}

void GenericMob::hasAI(bool b)
{
    if(b) {
        moveTimer->start();
    }
    else {
        moveTimer->stop();
    }
}


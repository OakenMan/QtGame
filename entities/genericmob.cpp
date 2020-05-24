#include "genericmob.h"

#include <QDebug>

GenericMob::GenericMob():Entity()
{
    // Timer pour le mouvement du mob
    moveTimer = new QTimer();
    moveTimer->setInterval(40); // <--- durée d'une frame en ms
    moveTimer->setTimerType(Qt::PreciseTimer);
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


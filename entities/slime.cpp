#include "slime.h"

#include <QDebug>

#include "physicsengine.h"

Slime::Slime():GenericMob()
{
    bodyType = eSlime;

    walk1 = QPixmap(":/enemies/ressources/Enemies/slimeWalk1.png");
    walk2 = QPixmap(":/enemies/ressources/Enemies/slimeWalk2.png");
    dead = QPixmap(":/enemies/ressources/Enemies/slimeDead.png");

    pixmap = walk1;

    direction = 1;
    setTransformOriginPoint(boundingRect().center());

    connect(moveTimer, &QTimer::timeout, this, &Slime::move);
}

QRectF Slime::boundingRect() const
{
    return QRectF(0, 0, DEFAULT_TILE_SIZE, 30);
}

void Slime::move()
{
    if(direction == 1) {
        if(PhysicsEngine::canMoveRight(this, true)) {
            this->moveBy(3, 0);
        }
        else {
            direction = -1;
            setTransform(QTransform());
        }
    }
    else if(direction == -1) {
        if(PhysicsEngine::canMoveLeft(this, true)) {
            this->moveBy(-3, 0);
        }
        else {
            direction = 1;
            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
        }
    }
}

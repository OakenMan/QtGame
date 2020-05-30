#include "fly.h"

#include "physicsengine.h"

Fly::Fly():GenericMob()
{
    bodyType = eFly;

    fly1 = QPixmap(":/enemies/ressources/Enemies/flyFly1.png");
    fly2 = QPixmap(":/enemies/ressources/Enemies/flyFly2.png");
    dead = QPixmap(":/enemies/ressources/Enemies/flyDead.png");

    pixmap = fly1;

    direction = -1;
    dist = 0;
    currentFrame = 0;
    setTransformOriginPoint(boundingRect().center());

    connect(moveTimer, &QTimer::timeout, this, &Fly::move);
}

QRectF Fly::boundingRect() const
{
    return QRectF(0, 0, 72, 36);
}

void Fly::move()
{
    if(direction == 1) {
        if(PhysicsEngine::canMoveRight(this, false) && dist<=240) {
            this->moveBy(5, 0);
            dist += 5;
            updatePixmap();
        }
        else {
            direction = -1;
            setTransform(QTransform());
        }
    }
    else if(direction == -1) {
        if(PhysicsEngine::canMoveLeft(this, false) && dist>=0) {
            this->moveBy(-5, 0);
            dist -= 5;
            updatePixmap();
        }
        else {
            direction = 1;
            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
        }
    }
}

void Fly::updatePixmap()
{
    currentFrame++;
    if(currentFrame == 5) {
        pixmap = fly2;
    }
    if(currentFrame == 10) {
        pixmap = fly1;
        currentFrame = 0;
    }
}

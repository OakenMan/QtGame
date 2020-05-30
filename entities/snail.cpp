#include "snail.h"

#include "physicsengine.h"

Snail::Snail()
{
    bodyType = eSnail;

    walk1 = QPixmap(":/enemies/ressources/Enemies/snailWalk1.png");
    walk2 = QPixmap(":/enemies/ressources/Enemies/snailWalk2.png");
    shell = QPixmap(":/enemies/ressources/Enemies/snailShell.png");
    dead = QPixmap(":/enemies/ressources/Enemies/snailShell_upsidedown.png");

    direction = -1;
    currentFrame = 0;
    setTransformOriginPoint(boundingRect().center());

    animationTimer = new QTimer();
    animationTimer->setInterval(5000);

    inShell = false;

    connect(moveTimer, &QTimer::timeout, this, &Snail::move);
    connect(animationTimer, &QTimer::timeout, this, &Snail::changePhase);

    animationTimer->start();
}

QRectF Snail::boundingRect() const
{
    return QRectF(0, 0, 54, 31);
}

void Snail::hasAI(bool b)
{
    if(b) {
        moveTimer->start();
        animationTimer->start();
    }
    else {
        moveTimer->stop();
        animationTimer->stop();
    }
}

bool Snail::isInShell()
{
    return inShell;
}

void Snail::move()
{
    if(inShell) {
        return;
    }

    if(direction == 1) {
        if(PhysicsEngine::canMoveRight(this, true)) {
            this->moveBy(2, 0);
            updatePixmap();
        }
        else {
            direction = -1;
            setTransform(QTransform());
        }
    }
    else if(direction == -1) {
        if(PhysicsEngine::canMoveLeft(this, true)) {
            this->moveBy(-2, 0);
            updatePixmap();
        }
        else {
            direction = 1;
            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
        }
    }
}

void Snail::changePhase()
{
    if(inShell) {
        inShell = false;
        pixmap = walk1;
    }
    else {
        inShell = true;
        pixmap = shell;
        update(boundingRect());
    }
}

void Snail::updatePixmap()
{
    if(inShell) {
        return;
    }
    currentFrame++;
    if(currentFrame == 5) {
        pixmap = walk1;
    }
    if(currentFrame == 10) {
        pixmap = walk2;
        currentFrame = 0;
    }
}

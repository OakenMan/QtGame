#include "poker.h"

#include <QPainter>

#include <QDebug>

#include "physicsengine.h"

Poker::Poker():GenericMob()
{
    bodyType = ePoker;

    mad = QPixmap(":/enemies/ressources/Enemies/pokerMad.png");
    sad = QPixmap(":/enemies/ressources/Enemies/pokerSad.png");

    pixmap = sad;

    animationTimer = new QTimer();
    animationTimer->setInterval(3000);

    outside = false;
    currentHeight = 40;

    connect(moveTimer, &QTimer::timeout, this, &Poker::move);
    connect(animationTimer, &QTimer::timeout, this, &Poker::changePhase);

    animationTimer->start();

    setZValue(-1);
}

QRectF Poker::boundingRect() const
{
    return QRectF(0, 0, DEFAULT_TILE_SIZE, 146);
}

void Poker::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    painter->drawPixmap(0, 0, DEFAULT_TILE_SIZE, 146, pixmap);

    Q_UNUSED(widget);
    Q_UNUSED(options);
}

void Poker::hasAI(bool b)
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

void Poker::move()
{
    if(outside) {
        if(currentHeight < 130) {
            moveBy(0, -10);
            currentHeight += 10;
        }
    }
    else {
        if(currentHeight >= 46) {
            moveBy(0, 5);
            currentHeight -= 5;
        }
    }
}

void Poker::changePhase()
{
    if(outside) {
        outside = false;
        pixmap = sad;
    }
    else {
        outside = true;
        pixmap = mad;
    }
}



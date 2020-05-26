#ifndef POKER_H
#define POKER_H

#include "genericmob.h"

class Poker: public GenericMob
{
public:
    Poker();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);
    void hasAI(bool b);

protected slots:
    void move();
    void changePhase();

private:
    QTimer *animationTimer;
    bool outside;
    int currentHeight;

    QPixmap mad;
    QPixmap sad;

};

#endif // POKER_H

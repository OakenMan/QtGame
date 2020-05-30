#ifndef SNAIL_H
#define SNAIL_H

#include "genericmob.h"

class Snail: public GenericMob
{
public:
    Snail();

    QRectF boundingRect() const;
    void hasAI(bool b);
    bool isInShell();

protected slots:
    void move();
    void changePhase();
    void updatePixmap();

private:
    QTimer *animationTimer;
    bool inShell;

    int direction;
    int currentFrame;

    QPixmap walk1;
    QPixmap walk2;
    QPixmap shell;
    QPixmap dead;
};

#endif // SNAIL_H

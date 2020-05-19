#ifndef PLAYER_H
#define PLAYER_H

#include "rigidbody.h"

/**
 * @brief Le joueur
 */
class Player : public RigidBody
{
public:
    Player();
    ~Player();

    int getDirection() const;
    void addDirection(int direction);

    bool isTouchingFoot(QGraphicsItem *item);
    bool isTouchingHead(QGraphicsItem *item);
    bool isTouchingPlatform(QGraphicsItem *item);

    QRectF boundingRect() const;

    void stand();
    void jump();
    void walk();
    void fall();

    bool isFalling();

    void nextFrame();

private:
    enum State {
        Standing = 0,
        Walking,
        Jumping,
        Falling
    };
    int direction;
    State state;

    QPixmap walkPixmap;
    QPixmap standPixmap;
    QPixmap jumpPixmap;
    QPixmap hurtPixmap;

    QPixmap walk1, walk2, walk3, walk4, walk5, walk6, walk7, walk8, walk9, walk10, walk11;

    int walkFrame;

};

#endif // PLAYER_H

#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>

/**
 * @brief Le joueur
 */
class Player : public QGraphicsItem
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
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

    void stand();
    void jump();
    void walk();
    void fall();

    bool isFalling();

private:
    enum State {
        Standing = 0,
        Walking,
        Jumping,
        Falling
    };
    int direction;
    State state;

};

#endif // PLAYER_H

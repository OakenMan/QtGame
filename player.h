#ifndef PLAYER_H
#define PLAYER_H

#include <QAbstractAnimation>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QPainterPath>
#include <QTimer>

#include "entities/entity.h"

/**
 * @brief Le joueur
 */
class Player : public Entity
{
    Q_OBJECT
    Q_PROPERTY(qreal jumpFactor READ getJumpFactor WRITE setJumpFactor NOTIFY jumpFactorChanged)

public:
    Player();
    ~Player();

    int getDirection() const;
    void addDirection(int direction);

    qreal getJumpFactor() const;
    void setJumpFactor(const qreal &newJumpFactor);

    void setLastPlatform(QGraphicsItem *item);

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

    void nextFrame();

private slots:
    void movePlayer();
    void jumpPlayer();
    void fallPlayer();
    void checkTimer();

signals:
    void jumpFactorChanged(qreal);

private:
    const int velocity = 7;
    const int jumpHeight = 140;

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

    bool dead;

    QPropertyAnimation *jumpAnimation;
    qreal jumpFactor;

    QTimer *moveTimer;
    QTimer *fallTimer;

    QGraphicsItem *lastPlatform;
    const qreal groundLevel = 672;

    RigidBody * collidingPlatforms();
    void checkCollisions();

    void die();

};

#endif // PLAYER_H

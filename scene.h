#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QAbstractAnimation>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QScrollBar>

#include "player.h"

/**
 * @brief Scene principale
 */
class Scene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(qreal jumpFactor READ getJumpFactor WRITE setJumpFactor NOTIFY jumpFactorChanged)

public:
    explicit Scene(QScrollBar *s, QObject *parent=nullptr);

    qreal getJumpFactor() const;
    void setJumpFactor(const qreal &jumpFactor);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void movePlayer();
    void jumpPlayer();
    void fallPlayer();

    void checkTimer();

    bool handleCollisionWithPlatform();
    QGraphicsItem * collidingPlatforms();

    void jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);

signals:
    void jumpFactorChanged(qreal);

private:
    Player * player;
    int velocity;
    int jumpHeight;

    QTimer * moveTimer;
    QTimer * fallTimer;

    QPropertyAnimation *jumpAnimation;
    qreal jumpFactor;

    QGraphicsItem *lastPlatform;
    qreal groundLevel;

    QScrollBar *scroll;

};

#endif // SCENE_H

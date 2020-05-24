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
#include "soundmanager.h"

/**
 * @brief Scene principale
 */
class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit Scene(QScrollBar *s, QObject *parent=nullptr);
    void startMobs();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    bool eventFilter(QObject *watched, QEvent *event);

    void drawForeground(QPainter *painter, const QRectF &rect);

public slots:
    void gameover();

private:
    Player * player;
    QScrollBar *scroll;
    QPointF cursor;
    bool dead;
};

#endif // SCENE_H

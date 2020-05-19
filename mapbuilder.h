#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include <QGraphicsScene>
#include <QScrollBar>

#include "rbodytype.h"
#include "rigidbody.h"

class MapBuilder : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit MapBuilder(QScrollBar *s, QObject *parent=nullptr);

    void setCurrentBlock(RBodyType block);

    void placeBlock(QPointF pos);
    void deleteBlock(QPointF pos);
    void placeGround();

    void setBackground(QString bg);
    QString getBackground();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    virtual void drawBackground(QPainter *painter, const QRectF &rect);

private:
    QScrollBar *scroll;
    RBodyType currentRBody;
    int action;

    QString background;
};

RigidBody *createRigidBody(RBodyType type);

#endif // MAPBUILDER_H

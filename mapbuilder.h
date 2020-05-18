#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include <QGraphicsScene>
#include <QScrollBar>

#include "rbodytype.h"

class MapBuilder : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit MapBuilder(QScrollBar *s, QObject *parent=nullptr);

    void setCurrentBlock(RBodyType block);

    void placeBlock(QPointF pos);
    void deleteBlock(QPointF pos);
    void placeGround();

    void setBackground(QPixmap bg);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    virtual void drawBackground(QPainter *painter, const QRectF &rect);

private:
    QScrollBar *scroll;
    RBodyType currentRBody;
    int action;

    QPixmap background;
};

#endif // MAPBUILDER_H

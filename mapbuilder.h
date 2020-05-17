#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include <QGraphicsScene>
#include <QScrollBar>

#include "blocks.h"

class MapBuilder : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit MapBuilder(QScrollBar *s, QObject *parent=nullptr);
    void setCurrentBlock(Blocks block);
    void placeBlock(QPointF pos);
    void deleteBlock(QPointF pos);
    void placeGround();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    virtual void drawBackground(QPainter *painter, const QRectF &rect);

private:
    QScrollBar *scroll;
    Blocks currentBlock;
    int action;

    QPixmap background;
};

#endif // MAPBUILDER_H

#include "mapbuilder.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>

MapBuilder::MapBuilder(QScrollBar *s, QObject *parent):QGraphicsScene(0, 0, 5000, 720, parent)
{
    scroll = s;

    setSceneRect(0, 0, 5000, 720);

    setCurrentBlock(pGrassPlatform);
}

void MapBuilder::setCurrentBlock(RBodyType block)
{
    currentRBody = block;
}

void MapBuilder::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF rawPos = event->scenePos();

    // Clic gauche ---> on pose un bloc
    if(event->button() == Qt::LeftButton) {
        action = 1;
        placeBlock(rawPos);
    }
    // Clic droit ---> on supprime les blocs
    if(event->button() == Qt::RightButton) {
        action = -1;
        deleteBlock(rawPos);
    }

    QGraphicsScene::mousePressEvent(event);
}

void MapBuilder::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF rawPos = event->scenePos();

    if(action == 1) {
        placeBlock(rawPos);
    }

    if(action == -1) {
        deleteBlock(rawPos);
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void MapBuilder::drawBackground(QPainter *painter, const QRectF &rect)
{
    for(int i=0; i<sceneRect().width(); i+=256) {
        for(int j=0; j<sceneRect().height(); j+=256) {
            painter->drawPixmap(i, j, 256, 256, QPixmap(background));
        }
    }

    Q_UNUSED(rect);
}

void MapBuilder::placeBlock(QPointF pos)
{
    if(!(items(pos).isEmpty())) {
        return;
    }

    QPointF newPos(((int)pos.x() / 48) * 48, ((int)pos.y() / 48) * 48);

    RigidBody *rb = createRigidBody(currentRBody);

    newPos.setY(newPos.y() + 48 - rb->boundingRect().height());

    addItem(rb);

    if(rb->getType() == ePoker) {
        newPos.setY(newPos.y() + 96);
    }
    rb->setPos(rb->mapFromScene(newPos));

    update(QRectF(newPos.x()-144, newPos.y()-144, 288, 288));
}

void MapBuilder::deleteBlock(QPointF pos)
{
    QList<QGraphicsItem*> list = items(pos);
    for(QGraphicsItem * item : list) {
        delete item;
    }
    update(QRectF(pos.x()-144, pos.y()-144, 288, 288));
}

void MapBuilder::placeGround()
{
    for(int i=0; i<5048; i+=48) {
        placeBlock(QPointF(i, 672));
    }
}

void MapBuilder::setBackground(QString bg)
{
    background = bg;
}

QString MapBuilder::getBackground()
{
    return background;
}

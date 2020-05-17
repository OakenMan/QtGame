#include "mapbuilder.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>

#include "blocks/groundbrick.h"
#include "blocks/solidbrick.h"
#include "blocks/platformbrick.h"
#include "blocks/bonusbox.h"

#include "player.h"

MapBuilder::MapBuilder(QScrollBar *s, QObject *parent):QGraphicsScene(0, 0, 8000, 720, parent)
{
    scroll = s;

    setSceneRect(0, 0, 8000, 720);

    setCurrentBlock(bGroundBrick);

    Player *player = new Player();
    addItem(player);
    player->setPos(48, 672 - player->boundingRect().height());
}

void MapBuilder::setCurrentBlock(Blocks block)
{
    currentBlock = block;
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

void MapBuilder::placeBlock(QPointF pos)
{
    if(!(items(pos).isEmpty())) {
        return;
    }

    QPointF newPos(((int)pos.x() / 48) * 48, ((int)pos.y() / 48) * 48);

    QGraphicsItem *block;

    switch(currentBlock) {
    case bGroundBrick:   block = new GroundBrick();      break;
    case bSolidBrick:    block = new SolidBrick();       break;
    case bPlatformBrick: block = new PlatformBrick();    break;
    case bBonusBox:      block = new BonusBox();         break;
    default:            break;
    }

    addItem(block);

    block->setPos(block->mapFromScene(newPos));
}

void MapBuilder::deleteBlock(QPointF pos)
{
    QList<QGraphicsItem*> list = items(pos);
    for(QGraphicsItem * item : list) {
        delete item;
    }
}

void MapBuilder::placeGround()
{
    setCurrentBlock(bGroundBrick);
    for(int i=0; i<8000/66; i++) {
        placeBlock(QPointF(i*48, 672));
    }
}

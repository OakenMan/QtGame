#include "mapbuilder.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include "tiles/grassplatform.h"
#include "tiles/dirtplatform.h"
#include "tiles/sandplatform.h"
#include "tiles/snowplatform.h"
#include "tiles/stoneplatform.h"
#include "tiles/castleplatform.h"
#include "tiles/water.h"
#include "tiles/lava.h"
#include "tiles/box.h"
#include "tiles/boxalt.h"
#include "tiles/boxempty.h"
#include "tiles/boxcoin.h"
#include "tiles/boxitem.h"
#include "tiles/signexit.h"
#include "tiles/signleft.h"
#include "tiles/signright.h"
#include "entities/coinbronze.h"
#include "entities/coinsilver.h"
#include "entities/coingold.h"

#include "player.h"

MapBuilder::MapBuilder(QScrollBar *s, QObject *parent):QGraphicsScene(0, 0, 8000, 720, parent)
{
    scroll = s;

    setSceneRect(0, 0, 8000, 720);

    setCurrentBlock(pGrassPlatform);

    Player *player = new Player();
    addItem(player);
    player->setPos(48, 672 - player->boundingRect().height());
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
            painter->drawPixmap(i, j, 256, 256, background);
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

    RigidBody *rb;

    switch(currentRBody) {
    case pGrassPlatform:    rb = new GrassPlatform();   break;
    case pDirtPlatform:     rb = new DirtPlatform();    break;
    case pSandPlatform:     rb = new SandPlatform();    break;
    case pSnowPlatform:     rb = new SnowPlatform();    break;
    case pStonePlatform:    rb = new StonePlatform();   break;
    case pCastlePlatform:   rb = new CastlePlatform();  break;
    case tWater:            rb = new Water();           break;
    case tLava:             rb = new Lava();            break;
    case tBox:              rb = new Box();             break;
    case tBoxAlt:           rb = new BoxAlt();          break;
    case tBoxEmpty:         rb = new BoxEmpty();        break;
    case tBoxCoin:          rb = new BoxCoin();         break;
    case tBoxItem:          rb = new BoxItem();         break;
    case iCoinBronze:       rb = new CoinBronze();      break;
    case iCoinSilver:       rb = new CoinSilver();      break;
    case iCoinGold:         rb = new CoinGold();        break;
    case dSignExit:         rb = new SignExit();        break;
    case dSignLeft:         rb = new SignLeft();        break;
    case dSignRight:        rb = new SignRight();       break;
    default:                                            break;
    }

    addItem(rb);

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
    setCurrentBlock(pGrassPlatform);
    for(int i=0; i<8000/66; i++) {
        placeBlock(QPointF(i*48, 672));
    }
}

void MapBuilder::setBackground(QPixmap bg)
{
    background = bg;
}

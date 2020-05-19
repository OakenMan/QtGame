#include "rigidbody.h"

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
#include "tiles/bush.h"
#include "tiles/cactus.h"
#include "tiles/rock.h"
#include "tiles/plant.h"
#include "tiles/snowhill.h"
#include "tiles/purpleplant.h"

#include "entities/coinbronze.h"
#include "entities/coinsilver.h"
#include "entities/coingold.h"

RigidBody::RigidBody()
{
    isSolid = true;

    pixmap = QPixmap(":/tiles/ressources/Tiles/box.png");
}

QRectF RigidBody::boundingRect() const
{
    return QRectF(0, 0, DEFAULT_TILE_SIZE, DEFAULT_TILE_SIZE);
}

void RigidBody::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    painter->drawPixmap(boundingRect().toRect(), pixmap);

    Q_UNUSED(widget);
    Q_UNUSED(options);
}

RBodyType RigidBody::getType()
{
    return bodyType;
}

RigidBody *createRigidBody(RBodyType type)
{
    switch(type) {
    case pGrassPlatform:    return new GrassPlatform();
    case pDirtPlatform:     return new DirtPlatform();
    case pSandPlatform:     return new SandPlatform();
    case pSnowPlatform:     return new SnowPlatform();
    case pStonePlatform:    return new StonePlatform();
    case pCastlePlatform:   return new CastlePlatform();
    case tWater:            return new Water();
    case tLava:             return new Lava();
    case tBox:              return new Box();
    case tBoxAlt:           return new BoxAlt();
    case tBoxEmpty:         return new BoxEmpty();
    case tBoxCoin:          return new BoxCoin();
    case tBoxItem:          return new BoxItem();
    case iCoinBronze:       return new CoinBronze();
    case iCoinSilver:       return new CoinSilver();
    case iCoinGold:         return new CoinGold();
    case dSignExit:         return new SignExit();
    case dSignLeft:         return new SignLeft();
    case dSignRight:        return new SignRight();
    case dBush:             return new Bush();
    case dRock:             return new Rock();
    case dSnowhill:         return new Snowhill();
    case dPlant:            return new Plant();
    case dPlantPurple:      return new PurplePlant();
    case dCactus:           return new Cactus();
    default:                return nullptr;
    }
}

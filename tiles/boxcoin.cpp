#include "boxcoin.h"

#include <QGraphicsScene>

BoxCoin::BoxCoin():Tile()
{
    bodyType = tBoxCoin;

    pixmap = QPixmap(":/tiles/ressources/Tiles/boxCoin.png");

    coins = 3;
}

void BoxCoin::breakBox()
{
    if(coins != 0) {
        coins--;

        RigidBody *rb = createRigidBody(iCoinGold);
        scene()->addItem(rb);

        if(coins == 2)
            rb->setPos(QPointF(pos().x(), pos().y()-48));
        if(coins == 1)
            rb->setPos(QPointF(pos().x()-48, pos().y()-48));
        if(coins == 0)
            rb->setPos(QPointF(pos().x()+48, pos().y()-48));

        update(QRectF(pos().x()-48, pos().y()-48, 144, 96));
    }
    if(coins == 0) {
        pixmap = QPixmap(":/tiles/ressources/Tiles/boxCoin_disabled.png");
        update(boundingRect());
    }
}

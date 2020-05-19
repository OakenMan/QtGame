#include "cactus.h"

Cactus::Cactus():Tile()
{
    bodyType = dCactus;

    solid = false;

    pixmap = QPixmap(":/items/ressources/Items/cactus.png");
}

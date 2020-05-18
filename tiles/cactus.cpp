#include "cactus.h"

Cactus::Cactus():Tile()
{
    bodyType = dCactus;

    isSolid = false;

    pixmap = QPixmap(":/items/ressources/Items/cactus.png");
}

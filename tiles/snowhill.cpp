#include "snowhill.h"

Snowhill::Snowhill():Tile()
{
    bodyType = dBush;

    isSolid = false;

    pixmap = QPixmap(":/items/ressources/Items/snowhill.png");
}

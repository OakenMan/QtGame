#include "snowhill.h"

Snowhill::Snowhill():Tile()
{
    bodyType = dBush;

    solid = false;

    pixmap = QPixmap(":/items/ressources/Items/snowhill.png");
}

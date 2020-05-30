#include "snowhill.h"

Snowhill::Snowhill():Tile()
{
    bodyType = dSnowhill;

    solid = false;

    pixmap = QPixmap(":/items/ressources/Items/snowhill.png");
}

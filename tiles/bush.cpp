#include "bush.h"

Bush::Bush():Tile()
{
    bodyType = dBush;

    solid = false;

    pixmap = QPixmap(":/items/ressources/Items/bush.png");
}

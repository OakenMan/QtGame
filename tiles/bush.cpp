#include "bush.h"

Bush::Bush():Tile()
{
    bodyType = dBush;

    isSolid = false;

    pixmap = QPixmap(":/items/ressources/Items/bush.png");
}

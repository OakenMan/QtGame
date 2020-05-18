#include "signleft.h"

SignLeft::SignLeft():Tile()
{
    bodyType = dSignLeft;

    isSolid = false;

    pixmap = QPixmap(":/tiles/ressources/Tiles/signLeft.png");
}

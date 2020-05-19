#include "signleft.h"

SignLeft::SignLeft():Tile()
{
    bodyType = dSignLeft;

    solid = false;

    pixmap = QPixmap(":/tiles/ressources/Tiles/signLeft.png");
}

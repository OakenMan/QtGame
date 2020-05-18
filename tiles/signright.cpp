#include "signright.h"

SignRight::SignRight():Tile()
{
    bodyType = dSignRight;

    isSolid = false;

    pixmap = QPixmap(":/tiles/ressources/Tiles/signRight.png");
}

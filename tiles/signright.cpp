#include "signright.h"

SignRight::SignRight():Tile()
{
    bodyType = dSignRight;

    solid = false;

    pixmap = QPixmap(":/tiles/ressources/Tiles/signRight.png");
}

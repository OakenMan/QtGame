#include "signexit.h"

SignExit::SignExit():Tile()
{
    bodyType = dSignExit;

    solid = false;

    pixmap = QPixmap(":/tiles/ressources/Tiles/signExit.png");
}

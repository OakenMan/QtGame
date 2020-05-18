#include "signexit.h"

SignExit::SignExit():Tile()
{
    bodyType = dSignExit;

    isSolid = false;

    pixmap = QPixmap(":/tiles/ressources/Tiles/signExit.png");
}

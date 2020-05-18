#include "box.h"

Box::Box():Tile()
{
    bodyType = tBox;

    pixmap = QPixmap(":/tiles/ressources/Tiles/box.png");
}

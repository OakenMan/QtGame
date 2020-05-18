#include "boxempty.h"

BoxEmpty::BoxEmpty():Tile()
{
    bodyType = tBoxEmpty;

    pixmap = QPixmap(":/tiles/ressources/Tiles/boxEmpty.png");
}

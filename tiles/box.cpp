#include "box.h"

Box::Box():Tile()
{
    bodyType = tBox;

    pixmap = QPixmap(":/tiles/ressources/Tiles/box.png");
}

void Box::breakBox()
{
    delete this;
//    pixmap = QPixmap(":/tiles/ressources/Tiles/boxEmpty.png");
//    update(boundingRect());
}

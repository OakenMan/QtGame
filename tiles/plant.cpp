#include "plant.h"

Plant::Plant():Tile()
{
    bodyType = dPlant;

    isSolid = false;

    pixmap = QPixmap(":/items/ressources/Items/plant.png");
}

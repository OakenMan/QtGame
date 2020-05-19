#include "plant.h"

Plant::Plant():Tile()
{
    bodyType = dPlant;

    solid = false;

    pixmap = QPixmap(":/items/ressources/Items/plant.png");
}

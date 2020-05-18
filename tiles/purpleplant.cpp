#include "purpleplant.h"

PurplePlant::PurplePlant():Tile()
{
    bodyType = dPlantPurple;

    isSolid = false;

    pixmap = QPixmap(":/items/ressources/Items/plantPurple.png");
}

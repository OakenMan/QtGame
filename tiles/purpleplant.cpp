#include "purpleplant.h"

PurplePlant::PurplePlant():Tile()
{
    bodyType = dPlantPurple;

    solid = false;

    pixmap = QPixmap(":/items/ressources/Items/plantPurple.png");
}

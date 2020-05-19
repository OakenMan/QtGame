#include "rock.h"

Rock::Rock():Tile()
{
    bodyType = dRock;

    solid = false;

    pixmap = QPixmap(":/items/ressources/Items/rock.png");
}

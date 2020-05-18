#include "rock.h"

Rock::Rock():Tile()
{
    bodyType = dRock;

    isSolid = false;

    pixmap = QPixmap(":/items/ressources/Items/rock.png");
}

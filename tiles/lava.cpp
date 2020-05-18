#include "lava.h"

Lava::Lava():GenericPlatform()
{
    bodyType = tLava;
    isSolid = false;

    basic = QPixmap(":/tiles/ressources/Tiles/liquidLavaTop_mid.png");
    center = QPixmap(":/tiles/ressources/Tiles/liquidLava.png");
    mid = QPixmap(":/tiles/ressources/Tiles/liquidLavaTop_mid.png");
    left = QPixmap(":/tiles/ressources/Tiles/liquidLavaTop_mid.png");
    right = QPixmap(":/tiles/ressources/Tiles/liquidLavaTop_mid.png");
}

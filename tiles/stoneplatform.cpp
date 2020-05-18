#include "stoneplatform.h"

StonePlatform::StonePlatform():GenericPlatform()
{
    bodyType = pStonePlatform;

    basic = QPixmap(":/tiles/ressources/Tiles/stone.png");
    center = QPixmap(":/tiles/ressources/Tiles/stoneCenter");
    mid = QPixmap(":/tiles/ressources/Tiles/stoneMid.png");
    left = QPixmap(":/tiles/ressources/Tiles/stoneLeft");
    right = QPixmap(":/tiles/ressources/Tiles/stoneRight");
}

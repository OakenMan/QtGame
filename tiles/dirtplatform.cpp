#include "dirtplatform.h"

DirtPlatform::DirtPlatform():GenericPlatform()
{
    bodyType = pDirtPlatform;

    basic = QPixmap(":/tiles/ressources/Tiles/dirt.png");
    center = QPixmap(":/tiles/ressources/Tiles/dirtCenter.png");
    mid = QPixmap(":/tiles/ressources/Tiles/dirtMid.png");
    left = QPixmap(":/tiles/ressources/Tiles/dirtLeft.png");
    right = QPixmap(":/tiles/ressources/Tiles/dirtRight.png");
}

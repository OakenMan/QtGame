#include "snowplatform.h"

SnowPlatform::SnowPlatform():GenericPlatform()
{
    bodyType = pSnowPlatform;

    basic = QPixmap(":/tiles/ressources/Tiles/snow.png");
    center = QPixmap(":/tiles/ressources/Tiles/snowCenter");
    mid = QPixmap(":/tiles/ressources/Tiles/snowMid.png");
    left = QPixmap(":/tiles/ressources/Tiles/snowLeft");
    right = QPixmap(":/tiles/ressources/Tiles/snowRight");
}

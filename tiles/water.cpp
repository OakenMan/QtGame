#include "water.h"

Water::Water():GenericPlatform()
{
    bodyType = tWater;
    solid = false;

    basic = QPixmap(":/tiles/ressources/Tiles/liquidWaterTop_mid.png");
    center = QPixmap(":/tiles/ressources/Tiles/liquidWater.png");
    mid = QPixmap(":/tiles/ressources/Tiles/liquidWaterTop_mid.png");
    left = QPixmap(":/tiles/ressources/Tiles/liquidWaterTop_mid.png");
    right = QPixmap(":/tiles/ressources/Tiles/liquidWaterTop_mid.png");
}

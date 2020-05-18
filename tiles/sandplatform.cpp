#include "sandplatform.h"

SandPlatform::SandPlatform():GenericPlatform()
{
    bodyType = pSandPlatform;

    basic = QPixmap(":/tiles/ressources/Tiles/sand.png");
    center = QPixmap(":/tiles/ressources/Tiles/sandCenter");
    mid = QPixmap(":/tiles/ressources/Tiles/sandMid.png");
    left = QPixmap(":/tiles/ressources/Tiles/sandLeft");
    right = QPixmap(":/tiles/ressources/Tiles/sandRight");
}

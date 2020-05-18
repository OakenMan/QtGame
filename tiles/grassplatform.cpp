#include "grassplatform.h"

GrassPlatform::GrassPlatform():GenericPlatform()
{
    bodyType = pGrassPlatform;

    basic = QPixmap(":/tiles/ressources/Tiles/grass.png");
    center = QPixmap(":/tiles/ressources/Tiles/grassCenter");
    mid = QPixmap(":/tiles/ressources/Tiles/grassMid.png");
    left = QPixmap(":/tiles/ressources/Tiles/grassLeft");
    right = QPixmap(":/tiles/ressources/Tiles/grassRight");
}

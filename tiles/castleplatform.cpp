#include "castleplatform.h"

CastlePlatform::CastlePlatform():GenericPlatform()
{
    bodyType = pCastlePlatform;

    basic = QPixmap(":/tiles/ressources/Tiles/castle.png");
    center = QPixmap(":/tiles/ressources/Tiles/castleCenter");
    mid = QPixmap(":/tiles/ressources/Tiles/castleMid.png");
    left = QPixmap(":/tiles/ressources/Tiles/castleLeft");
    right = QPixmap(":/tiles/ressources/Tiles/castleRight");
}

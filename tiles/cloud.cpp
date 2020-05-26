#include "cloud.h"

Cloud::Cloud()
{
    bodyType = dCloud;

    solid = false;

    int r = rand() % 3;
    switch (r) {
    case 0: pixmap = QPixmap(":/items/ressources/Items/cloud1.png"); break;
    case 1: pixmap = QPixmap(":/items/ressources/Items/cloud2.png"); break;
    case 2: pixmap = QPixmap(":/items/ressources/Items/cloud3.png"); break;
    }
}

QRectF Cloud::boundingRect() const
{
    return QRectF(0, 0, 129, 71);
}

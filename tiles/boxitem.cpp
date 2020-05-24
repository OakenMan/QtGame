#include "boxitem.h"

BoxItem::BoxItem():Tile()
{
    bodyType = tBoxItem;

    pixmap = QPixmap(":/tiles/ressources/Tiles/boxItem.png");
}

void BoxItem::breakBox()
{


}

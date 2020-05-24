#ifndef BOXCOIN_H
#define BOXCOIN_H

#include "tile.h"

class BoxCoin: public Tile
{  
    Q_OBJECT

public:
    BoxCoin();

public slots:
    void breakBox();

private:
    int coins;
};

#endif // BOXCOIN_H

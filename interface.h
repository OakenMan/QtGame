#ifndef INTERFACE_H
#define INTERFACE_H

#include <QPainter>

#include "scene.h"
#include "player.h"

class Interface: public QObject
{
    Q_OBJECT;

public:
    explicit Interface(Scene *newScene, Player *newPlayer, QScrollBar *s);

public slots:
    void updateHUD();
    void moveInterface(int dx);

private:
    QScrollBar *scroll;
    Scene *scene;
    Player *player;
};

#endif // INTERFACE_H

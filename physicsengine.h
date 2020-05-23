#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "scene.h"
#include "player.h"

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QAbstractAnimation>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QScrollBar>

#include "entities/entity.h"

class PhysicsEngine: public QObject
{
    Q_OBJECT

public:
    explicit PhysicsEngine(Scene *newScene);

    static bool canMoveRight(Entity *entity, bool cantFall);
    static bool canMoveLeft(Entity *entity, bool cantFall);
    static bool canMoveUp(Entity *entity);
    static bool canMoveDown(Entity *entity);

private:
    static Scene *scene;

};

#endif // PHYSICSENGINE_H

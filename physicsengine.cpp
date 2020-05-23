#include "physicsengine.h"

#include "rigidbody.h"

Scene * PhysicsEngine::scene;

PhysicsEngine::PhysicsEngine(Scene *newScene) {
    PhysicsEngine::scene = newScene;
}

/**
 * Renvoie true si l'entité peut aller à droite, false si elle est bloqué
 */
bool PhysicsEngine::canMoveRight(Entity *entity, bool cantFall)
{
    QRectF entityRect = entity->mapRectToScene(entity->boundingRect());

    QList<QGraphicsItem*> items = scene->collidingItems(entity);
    for(QGraphicsItem *item : items) {
        RigidBody* rb = qgraphicsitem_cast<RigidBody*>(item);
        if(rb->isSolid()) {
            QRectF itemRect = rb->mapRectToScene(rb->boundingRect());
            if(entityRect.right() <= itemRect.right()-7) {
                return false;
            }
        }
    }

    if(cantFall) {
        QList<QGraphicsItem*> items = scene->items(QRectF(entityRect.left()+48, entityRect.bottom(), 48, 48));
        for(QGraphicsItem *item: items) {
            RigidBody *rb = qgraphicsitem_cast<RigidBody*>(item);
            if(rb->isSolid()) {
                return true;
            }
        }
        return false;
    }


    return true;
}

/**
 * Renvoie true si l'entité peut aller à gauche, false si elle est bloqué
 */
bool PhysicsEngine::canMoveLeft(Entity *entity, bool cantFall)
{
    QRectF entityRect = entity->mapRectToScene(entity->boundingRect());

    QList<QGraphicsItem*> items = scene->collidingItems(entity);
    for(QGraphicsItem *item : items) {
        RigidBody* rb = qgraphicsitem_cast<RigidBody*>(item);
        if(rb->isSolid()) {
            QRectF itemRect = rb->mapRectToScene(rb->boundingRect());
            if(entityRect.left() >= itemRect.left()+7) {
                return false;
            }
        }
    }

    if(cantFall) {
        QList<QGraphicsItem*> items = scene->items(QRectF(entityRect.left()-48, entityRect.bottom(), 48, 48));
        for(QGraphicsItem *item: items) {
            RigidBody *rb = qgraphicsitem_cast<RigidBody*>(item);
            if(rb->isSolid()) {
                return true;
            }
        }
        return false;
    }

    return true;
}

/**
 * Renvoie true si l'entité peut aller en haut, false si elle est bloqué
 */
bool PhysicsEngine::canMoveUp(Entity *entity)
{
    QRectF entityRect = entity->mapRectToScene(entity->boundingRect());

    QList<QGraphicsItem*> items = scene->collidingItems(entity);
    for(QGraphicsItem *item : items) {
        RigidBody* rb = qgraphicsitem_cast<RigidBody*>(item);
        if(rb->isSolid()) {
            QRectF itemRect = rb->mapRectToScene(rb->boundingRect());
            // Si le haut du joueur est en dessous du bas de la plateforme
            if(entityRect.top() >= itemRect.bottom()-10) {
                // Si la plateforme est au dessus du joueur (et pas sur les côtés)
                if(itemRect.center().x() >= entityRect.left() && itemRect.center().x() <= entityRect.right()) {
                    return false;
                }
            }
        }
    }

    return true;
}

/**
 * Renvoie true si l'entité peut aller en bas, false si elle est bloqué
 */
bool PhysicsEngine::canMoveDown(Entity *entity)
{
//    QRectF entityRect = entity->mapRectToScene(entity->boundingRect());

//    QList<QGraphicsItem*> items = entity->collidingItems();

//    qDebug() << "in canMoveDown : " << items.isEmpty();

//    for(QGraphicsItem *item : items) {
//        RigidBody* rb = qgraphicsitem_cast<RigidBody*>(item);
//        if(rb->isSolid()) {
//            QRectF itemRect = rb->mapRectToScene(rb->boundingRect());
//            // Si le bas du joueur est au dessus du haut de la plateforme
//            if(entityRect.bottom() <= itemRect.top()+24) {
//                // Si la plateforme est au dessus du joueur (et pas sur les côtés)
//                if(itemRect.center().x() >= entityRect.left() && itemRect.center().x() <= entityRect.right()) {
//                    return false;
//                }
//            }
//        }
//    }

//    return true;
    QRectF entityRect = entity->mapRectToScene(entity->boundingRect());

    QRectF blockBottom(entityRect.left(), entityRect.bottom(), 48, 48);

    QList<QGraphicsItem*> items = scene->items(blockBottom);

    for(QGraphicsItem *item : items) {
            RigidBody* rb = qgraphicsitem_cast<RigidBody*>(item);
            if(rb->isSolid()) {
//                QRectF itemRect = rb->mapRectToScene(rb->boundingRect());
//                // Si le bas du joueur est au dessus du haut de la plateforme
//                if(entityRect.bottom() <= itemRect.top()+24) {
//                    // Si la plateforme est au dessus du joueur (et pas sur les côtés)
//                    if(itemRect.center().x() >= entityRect.left() && itemRect.center().x() <= entityRect.right()) {
//                        return false;
//                    }
//                }
                return false;
            }
        }
    return true;
}

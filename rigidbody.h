#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <QGraphicsItem>
#include <QGraphicsObject>

#include "rbodytype.h"

class RigidBody : public QGraphicsObject
{

public:
    RigidBody();

    // Overrides de QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);
    int type() const override { return UserType + 1; }

    // Nouvelles méthodes
    void onCollide();
    RBodyType getType();
    bool isSolid();

    // Constantes
    const int DEFAULT_TILE_SIZE = 48;

protected:
    RBodyType bodyType;
    QPixmap pixmap;         // Texture affichée à l'écran
    bool solid;
};

RigidBody * createRigidBody(RBodyType type);

#endif // RIGIDBODY_H

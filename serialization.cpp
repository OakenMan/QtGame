#include "serialization.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include "mapbuilder.h"

/**
 * Lis un document Json et rajoute les différents éléments à la scène actuelle
 */
void Serialization::loadMap(const QJsonDocument loadData, QGraphicsScene *scene)
{
    QJsonObject mainObject = loadData.object();
    QJsonArray array = mainObject["items"].toArray();
    QString background = mainObject["background"].toString();

    for(int i=0; i<array.size(); i++) {
        QJsonObject item = array[i].toObject();
        qreal x = item["x"].toDouble();
        qreal y = item["y"].toDouble();
        RBodyType type = static_cast<RBodyType>(item["type"].toInt());

        QPointF newPos(((int)x / 48) * 48, ((int)y / 48) * 48);

        RigidBody *rb = createRigidBody(type);

        newPos.setY(newPos.y() + 48 - rb->boundingRect().height());

        scene->addItem(rb);

        if(rb->getType() == ePoker) {
            newPos.setY(newPos.y() + 144);
        }
        rb->setPos(rb->mapFromScene(newPos));

        scene->setBackgroundBrush(QBrush(QPixmap(background)));
    }
}

/**
 * Écrit les différents éléments de la scène actuelle sur un document Json
 * Structure du Json :
 *  {
 *  items: [
 *          {
 *              x: position x
 *              y: position y
 *              type: type d'élément
 *          },
 *          ...
 *         ]
 *  }
 */
QJsonDocument Serialization::saveMap(MapBuilder *scene)
{
    QJsonObject mainObject;
    QJsonArray array;

    QList<QGraphicsItem*> items = scene->items(scene->sceneRect());
    for(QGraphicsItem *item: items) {
        RigidBody *rb = qgraphicsitem_cast<RigidBody*>(item);
        QJsonObject jsonItem;
        jsonItem["x"] = rb->pos().x();
        jsonItem["y"] = rb->pos().y();
        jsonItem["type"] = rb->getType();
        array.append(jsonItem);
    }

    mainObject["items"] = array;
    mainObject["background"] = scene->getBackground();

    QJsonDocument saveData(mainObject);

    return saveData;
}

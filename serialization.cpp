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
void loadMap(const QJsonDocument loadData, QGraphicsScene *scene)
{
    QJsonObject mainObject = loadData.object();
    QJsonArray array = mainObject["items"].toArray();
    QString background = mainObject["background"].toString();

    for(int i=0; i<array.size(); i++) {
        QJsonObject item = array[i].toObject();
        qreal x = item["x"].toDouble();
        qreal y = item["y"].toDouble();
        RBodyType type = static_cast<RBodyType>(item["type"].toInt());

        RigidBody * block = createRigidBody(type);

        QPointF newPos(x, y);
        newPos.setY(newPos.y() + 48 - block->boundingRect().height());

        scene->addItem(block);
        block->setPos(newPos);

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
QJsonDocument saveMap(MapBuilder *scene)
{
    QJsonObject mainObject;
    QJsonArray array;

    // Parcours toute la scène "case par case", vérifie si il y a un objet et si oui, l'ajoute au Json
    for(int i=24; i<scene->sceneRect().width(); i+=48) {
        for(int j=24; j<scene->sceneRect().height(); j+=48) {
            QList<QGraphicsItem*> list = scene->items(QPointF((qreal)i, (qreal)j));
            if(!list.isEmpty()) {
                RigidBody *item = (RigidBody*)list.at(0);
                QJsonObject block;
                block["x"] = i-24;
                block["y"] = j-24;
                block["type"] = item->getType();
                array.append(block);
            }
        }
    }

    mainObject["items"] = array;
    mainObject["background"] = scene->getBackground();

    QJsonDocument saveData(mainObject);

    return saveData;
}

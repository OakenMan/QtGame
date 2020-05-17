#include "serialization.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include "blocks/groundbrick.h"
#include "blocks/solidbrick.h"
#include "blocks/platformbrick.h"
#include "blocks/bonusbox.h"

/**
 * Lis un document Json et rajoute les différents éléments à la scène actuelle
 */
void loadMap(const QJsonDocument loadData, QGraphicsScene *scene)
{
    QJsonObject mainObject = loadData.object();
    QJsonArray array = mainObject["items"].toArray();

    for(int i=0; i<array.size(); i++) {
        QJsonObject item = array[i].toObject();
        qreal x = item["x"].toDouble();
        qreal y = item["y"].toDouble();
        int type = item["type"].toInt();

        QGraphicsItem *block;
        const int usertype = QGraphicsItem::UserType;

        // [!] Pour chaque ajout d'élément, les rajouter ici :
        switch(type) {
        case usertype+2: block = new GroundBrick();     break;
        case usertype+3: block = new SolidBrick();      break;
        case usertype+4: block = new PlatformBrick();   break;
        case usertype+5: block = new BonusBox();        break;
        default: break;
        }

        scene->addItem(block);
        block->setPos(block->mapFromScene(QPointF(x, y)));
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
QJsonDocument saveMap(QGraphicsScene *scene)
{
    QJsonObject mainObject;
    QJsonArray array;

    // Parcours toute la scène "case par case", vérifie si il y a un objet et si oui, l'ajoute au Json
    for(int i=24; i<scene->sceneRect().width(); i+=48) {
        for(int j=24; j<scene->sceneRect().height(); j+=48) {
            QList<QGraphicsItem*> list = scene->items(QPointF((qreal)i, (qreal)j));
            if(!list.isEmpty()) {
                QGraphicsItem *item = list.at(0);
                QJsonObject block;
                block["x"] = i-24;
                block["y"] = j-24;
                block["type"] = item->type();
                array.append(block);
            }
        }
    }

    mainObject["items"] = array;

    QJsonDocument saveData(mainObject);

    return saveData;
}

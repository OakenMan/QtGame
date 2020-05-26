#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <QJsonDocument>
#include <QGraphicsScene>

#include "mapbuilder.h"

class Serialization: public QObject
{
    Q_OBJECT

public:
    static void loadMap(const QJsonDocument loadData, QGraphicsScene *scene);
    static QJsonDocument saveMap(MapBuilder *scene);
};

#endif // SERIALIZATION_H

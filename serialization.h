#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <QJsonDocument>
#include <QGraphicsScene>

#include "mapbuilder.h"

void loadMap(const QJsonDocument loadData, QGraphicsScene *scene);
QJsonDocument saveMap(MapBuilder *scene);

#endif // SERIALIZATION_H

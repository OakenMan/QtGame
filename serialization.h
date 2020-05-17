#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <QJsonDocument>
#include <QGraphicsScene>

void loadMap(const QJsonDocument loadData, QGraphicsScene *scene);
QJsonDocument saveMap(QGraphicsScene *scene);

#endif // SERIALIZATION_H

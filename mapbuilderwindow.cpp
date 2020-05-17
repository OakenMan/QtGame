#include "mapbuilderwindow.h"
#include "ui_mapbuilderwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QGraphicsItem>

#include "blocks/groundbrick.h"
#include "blocks/solidbrick.h"
#include "blocks/platformbrick.h"
#include "blocks/bonusbox.h"

MapBuilderWindow::MapBuilderWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MapBuilderWindow)
{
    ui->setupUi(this);

    scene = new MapBuilder(ui->graphicsView->horizontalScrollBar(), this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(QSize(1280, 720));

    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MapBuilderWindow::~MapBuilderWindow()
{
    delete ui;
}

/**
 * Lis un document Json et rajoute les différents éléments à la scène actuelle
 */
void MapBuilderWindow::loadMap(const QJsonDocument loadData)
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
QJsonDocument MapBuilderWindow::saveMap()
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

void MapBuilderWindow::on_groundBrickButton_toggled(bool checked)
{
    if(checked) {
        ui->solidBrickButton->setChecked(false);
        ui->platformBrickButton->setChecked(false);
        ui->bonusBoxButton->setChecked(false);

        scene->setCurrentBlock(bGroundBrick);
    }
}

void MapBuilderWindow::on_solidBrickButton_toggled(bool checked)
{
    if(checked) {
        ui->groundBrickButton->setChecked(false);
        ui->platformBrickButton->setChecked(false);
        ui->bonusBoxButton->setChecked(false);

        scene->setCurrentBlock(bSolidBrick);
    }
}

void MapBuilderWindow::on_platformBrickButton_toggled(bool checked)
{
    if(checked) {
        ui->solidBrickButton->setChecked(false);
        ui->groundBrickButton->setChecked(false);
        ui->bonusBoxButton->setChecked(false);

        scene->setCurrentBlock(bPlatformBrick);
    }
}

void MapBuilderWindow::on_bonusBoxButton_toggled(bool checked)
{
    if(checked) {
        ui->solidBrickButton->setChecked(false);
        ui->platformBrickButton->setChecked(false);
        ui->groundBrickButton->setChecked(false);

        scene->setCurrentBlock(bBonusBox);
    }
}

void MapBuilderWindow::on_placeGroundButton_clicked()
{
    scene->placeGround();
}

/**
 * Sauvegarde la map
 */
void MapBuilderWindow::on_actionSauvegarder_le_niveau_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save the file");

    QFile saveFile(fileName);

    if(!saveFile.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + saveFile.errorString());
        return;
    }

    QJsonDocument saveDoc = saveMap();

    saveFile.write(saveDoc.toJson(QJsonDocument::Compact));
}

/**
 * Charge une map
 */
void MapBuilderWindow::on_actionCharger_un_niveau_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

    QFile loadFile(fileName);

    if(!loadFile.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + loadFile.errorString());
        return;
    }

    QByteArray loadData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));

    loadMap(loadDoc);
}

/**
 * Reset la map
 */
void MapBuilderWindow::on_actionNouveau_niveau_triggered()
{
    QList<QGraphicsItem*> items = scene->items(QRectF(0, 0, 8000, 720));
    for(QGraphicsItem *item : items) {
        delete item;
    }
}

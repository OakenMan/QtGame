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

#include "serialization.h"

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

    QJsonDocument saveDoc = saveMap(scene);

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

    loadMap(loadDoc, scene);
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

#include "mapbuilderwindow.h"
#include "ui_mapbuilderwindow.h"

#include <QDebug>

MapBuilderWindow::MapBuilderWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MapBuilderWindow)
{
    ui->setupUi(this);
//    this->setCentralWidget(ui->graphicsView);

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
    qDebug() << checked;
    if(checked) {
        ui->solidBrickButton->setChecked(false);
        ui->platformBrickButton->setChecked(false);
        ui->bonusBoxButton->setChecked(false);

        scene->setCurrentBlock(bGroundBrick);
    }
}

void MapBuilderWindow::on_solidBrickButton_toggled(bool checked)
{
    qDebug() << checked;
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

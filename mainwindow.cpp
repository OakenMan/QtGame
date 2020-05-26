#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonDocument>
#include <QDebug>

#include "serialization.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->graphicsView);

    // On place la fenêtre au centre de l'écran
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    // Création de la scene principale
    scene = new Scene(ui->graphicsView->horizontalScrollBar(), this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(QSize(1280, 720));

    // On fait disparaitre les scrollbars
//    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsView->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_map_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

    QFile loadFile(fileName);

    if(!loadFile.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + loadFile.errorString());
        return;
    }

    QByteArray loadData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
    Serialization::loadMap(loadDoc, scene);

    scene->startMobs();

    ui->graphicsView->horizontalScrollBar()->setValue(0);
}

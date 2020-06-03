#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>

#include "serialization.h"
#include "rigidbody.h"

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

    // On fait disparaitre les scrollbars et les bords de l'écran
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->statusBar->hide();
    ui->mainToolBar->hide();
    ui->menuBar->hide();

    // Pour pouvoir récupérer les inputs souris depuis la scene
    ui->graphicsView->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

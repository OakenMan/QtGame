#include "launcher.h"
#include "ui_launcher.h"

#include <QDesktopWidget>

#include "mainwindow.h"
#include "mapbuilderwindow.h"

Launcher::Launcher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Launcher)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // On place le launcher au centre de l'écran
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
}

Launcher::~Launcher()
{
    delete ui;
}

void Launcher::on_pushButton_clicked()
{
    close();
}

/**
 * Lance le jeu
 */
void Launcher::on_gameButton_clicked()
{
    window = new MainWindow();
    window->show();
    window->raise();
    window->activateWindow();
    this->close();
}

/**
 * Lance l'editeur de maps
 */
void Launcher::on_mapEditorButton_clicked()
{
    window = new MapBuilderWindow();
    window->show();
    window->raise();
    window->activateWindow();
    this->close();
}

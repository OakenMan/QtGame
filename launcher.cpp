#include "launcher.h"
#include "ui_launcher.h"

#include <QDesktopWidget>
#include <QFont>

#include "mainwindow.h"
#include "mapbuilderwindow.h"

Launcher::Launcher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Launcher)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    setAttribute(Qt::WA_TranslucentBackground);
//    setAttribute(Qt::WA_NoSystemBackground);
//    setAttribute(Qt::WA_TransparentForMouseEvents);

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

void Launcher::on_gameButton_clicked()
{
    //    this->showMinimized();
    window = new MainWindow();
    window->show();
    window->raise();
    window->activateWindow();
}

void Launcher::on_mapEditorButton_clicked()
{
    //    this->showMinimized();
    window = new MapBuilderWindow();
    window->show();
    window->raise();
    window->activateWindow();
}

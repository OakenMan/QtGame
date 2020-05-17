#include <QApplication>

#include "mainwindow.h"
#include "mapbuilderwindow.h"

int main(int argc, char *argv[])
{   
    QApplication a(argc, argv);

//    MainWindow w;
//    w.show();

    MapBuilderWindow w;
    w.show();

    return a.exec();
}

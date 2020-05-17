#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "scene.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief Fenêtre principale de l'application
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionLoad_map_triggered();

private:
    Ui::MainWindow *ui;
    Scene *scene;
};

#endif // MAINWINDOW_H

#ifndef MAPBUILDERWINDOW_H
#define MAPBUILDERWINDOW_H

#include <QMainWindow>

#include "mapbuilder.h"

namespace Ui {
class MapBuilderWindow;
}

class MapBuilderWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapBuilderWindow(QWidget *parent = 0);
    ~MapBuilderWindow();

private slots:
    void on_groundBrickButton_toggled(bool checked);
    void on_solidBrickButton_toggled(bool checked);
    void on_platformBrickButton_toggled(bool checked);
    void on_bonusBoxButton_toggled(bool checked);

    void on_placeGroundButton_clicked();

    void on_actionSauvegarder_le_niveau_triggered();
    void on_actionCharger_un_niveau_triggered();

    void on_actionNouveau_niveau_triggered();

private:
    Ui::MapBuilderWindow *ui;
    MapBuilder *scene;
};

#endif // MAPBUILDERWINDOW_H

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
    void on_placeGroundButton_clicked();

    void on_actionSauvegarder_le_niveau_triggered();
    void on_actionCharger_un_niveau_triggered();

    void on_actionNouveau_niveau_triggered();

    void on_pGrassPlatformBtn_clicked();

    void on_pSandPlatformBtn_clicked();

    void on_pSnowPlatformBtn_clicked();

    void on_pDirtPlatformBtn_clicked();

    void on_pStonePlatformBtn_clicked();

    void on_pCastlePlatformBtn_clicked();


    void on_tWaterBtn_clicked();

    void on_tLavaBtn_clicked();

    void on_bgSkyBtn_clicked();

    void on_bgCastleBtn_clicked();

    void on_tBoxItemBtn_clicked();

    void on_tBoxCoinBtn_clicked();

    void on_tBoxEmptyBtn_clicked();

    void on_tBoxBtn_clicked();

    void on_tBoxAltBtn_clicked();

    void on_iCoinBronzeBtn_clicked();

    void on_iCoinSilverBtn_clicked();

    void on_iCoinGoldBtn_clicked();

    void on_dSignExitBtn_clicked();

    void on_dSignLeftBtn_clicked();

    void on_dSignRightBtn_clicked();

    void on_dBushBtn_clicked();

    void on_dSnowhillBtn_clicked();

    void on_dRockBtn_clicked();

    void on_dPurplePlantBtn_clicked();

    void on_dPlantBtn_clicked();

    void on_dCactusBtn_clicked();

private:
    Ui::MapBuilderWindow *ui;
    MapBuilder *scene;
    void resetButtons();
};

#endif // MAPBUILDERWINDOW_H

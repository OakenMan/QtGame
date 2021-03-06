#include "mapbuilderwindow.h"
#include "ui_mapbuilderwindow.h"

#include <QDesktopWidget>
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

    // On place la fenêtre au centre de l'écran
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    // Création de la scene
    scene = new MapBuilder(ui->graphicsView->horizontalScrollBar(), this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(QSize(1280, 720));

    // On fait disparaitre les scrollbars et la status bar
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->statusbar->hide();

    ui->currentRBDisplay->setIcon(ui->pGrassPlatformBtn->icon());
}

MapBuilderWindow::~MapBuilderWindow()
{
    delete ui;
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

    QJsonDocument saveDoc = Serialization::saveMap(scene);

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

    Serialization::loadMap(loadDoc, scene);
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

// ------------------ SLOTS DES BOUTONS ---------------- //

void MapBuilderWindow::on_bgSkyBtn_clicked()
{
    scene->setBackground(":/tiles/ressources/bg.png");
    scene->update(scene->sceneRect());
}

void MapBuilderWindow::on_bgCastleBtn_clicked()
{
    scene->setBackground(":/tiles/ressources/bg_castle.png");
    scene->update(scene->sceneRect());
}

void MapBuilderWindow::on_pGrassPlatformBtn_clicked()
{
    scene->setCurrentBlock(pGrassPlatform);
    ui->currentRBDisplay->setIcon(ui->pGrassPlatformBtn->icon());
}

void MapBuilderWindow::on_pSandPlatformBtn_clicked()
{
    scene->setCurrentBlock(pSandPlatform);
    ui->currentRBDisplay->setIcon(ui->pSandPlatformBtn->icon());
}

void MapBuilderWindow::on_pSnowPlatformBtn_clicked()
{
    scene->setCurrentBlock(pSnowPlatform);
    ui->currentRBDisplay->setIcon(ui->pSnowPlatformBtn->icon());
}

void MapBuilderWindow::on_pDirtPlatformBtn_clicked()
{
    scene->setCurrentBlock(pDirtPlatform);
    ui->currentRBDisplay->setIcon(ui->pDirtPlatformBtn->icon());
}

void MapBuilderWindow::on_pStonePlatformBtn_clicked()
{
    scene->setCurrentBlock(pStonePlatform);
    ui->currentRBDisplay->setIcon(ui->pStonePlatformBtn->icon());
}

void MapBuilderWindow::on_pCastlePlatformBtn_clicked()
{
    scene->setCurrentBlock(pCastlePlatform);
    ui->currentRBDisplay->setIcon(ui->pCastlePlatformBtn->icon());
}

void MapBuilderWindow::on_tWaterBtn_clicked()
{
    scene->setCurrentBlock(tWater);
    ui->currentRBDisplay->setIcon(ui->tWaterBtn->icon());
}

void MapBuilderWindow::on_tLavaBtn_clicked()
{
    scene->setCurrentBlock(tLava);
    ui->currentRBDisplay->setIcon(ui->tLavaBtn->icon());
}

void MapBuilderWindow::on_tBoxItemBtn_clicked()
{
    scene->setCurrentBlock(tBoxItem);
    ui->currentRBDisplay->setIcon(ui->tBoxItemBtn->icon());
}

void MapBuilderWindow::on_tBoxCoinBtn_clicked()
{
    scene->setCurrentBlock(tBoxCoin);
    ui->currentRBDisplay->setIcon(ui->tBoxCoinBtn->icon());
}

void MapBuilderWindow::on_tBoxEmptyBtn_clicked()
{
    scene->setCurrentBlock(tBoxEmpty);
    ui->currentRBDisplay->setIcon(ui->tBoxEmptyBtn->icon());
}

void MapBuilderWindow::on_tBoxBtn_clicked()
{
    scene->setCurrentBlock(tBox);
    ui->currentRBDisplay->setIcon(ui->tBoxBtn->icon());
}

void MapBuilderWindow::on_tBoxAltBtn_clicked()
{
    scene->setCurrentBlock(tBoxAlt);
    ui->currentRBDisplay->setIcon(ui->tBoxAltBtn->icon());
}

void MapBuilderWindow::on_iCoinBronzeBtn_clicked()
{
    scene->setCurrentBlock(iCoinBronze);
    ui->currentRBDisplay->setIcon(ui->iCoinBronzeBtn->icon());
}

void MapBuilderWindow::on_iCoinSilverBtn_clicked()
{
    scene->setCurrentBlock(iCoinSilver);
    ui->currentRBDisplay->setIcon(ui->iCoinSilverBtn->icon());
}

void MapBuilderWindow::on_iCoinGoldBtn_clicked()
{
    scene->setCurrentBlock(iCoinGold);
    ui->currentRBDisplay->setIcon(ui->iCoinGoldBtn->icon());
}

void MapBuilderWindow::on_dSignExitBtn_clicked()
{
    scene->setCurrentBlock(dSignExit);
    ui->currentRBDisplay->setIcon(ui->dSignExitBtn->icon());
}

void MapBuilderWindow::on_dSignLeftBtn_clicked()
{
    scene->setCurrentBlock(dSignLeft);
    ui->currentRBDisplay->setIcon(ui->dSignLeftBtn->icon());
}

void MapBuilderWindow::on_dSignRightBtn_clicked()
{
    scene->setCurrentBlock(dSignRight);
    ui->currentRBDisplay->setIcon(ui->dSignRightBtn->icon());
}

void MapBuilderWindow::on_dBushBtn_clicked()
{
    scene->setCurrentBlock(dBush);
    ui->currentRBDisplay->setIcon(ui->dBushBtn->icon());
}

void MapBuilderWindow::on_dSnowhillBtn_clicked()
{
    scene->setCurrentBlock(dSnowhill);
    ui->currentRBDisplay->setIcon(ui->dSnowhillBtn->icon());
}

void MapBuilderWindow::on_dRockBtn_clicked()
{
    scene->setCurrentBlock(dRock);
    ui->currentRBDisplay->setIcon(ui->dRockBtn->icon());
}

void MapBuilderWindow::on_dPurplePlantBtn_clicked()
{
    scene->setCurrentBlock(dPlantPurple);
    ui->currentRBDisplay->setIcon(ui->dPurplePlantBtn->icon());
}

void MapBuilderWindow::on_dPlantBtn_clicked()
{
    scene->setCurrentBlock(dPlant);
    ui->currentRBDisplay->setIcon(ui->dPlantBtn->icon());
}

void MapBuilderWindow::on_dCactusBtn_clicked()
{
    scene->setCurrentBlock(dCactus);
    ui->currentRBDisplay->setIcon(ui->dCactusBtn->icon());
}

void MapBuilderWindow::on_dCloudBtn_clicked()
{
    scene->setCurrentBlock(dCloud);
    ui->currentRBDisplay->setIcon(ui->dCloudBtn->icon());
}

void MapBuilderWindow::on_eSlimeBtn_clicked()
{
    scene->setCurrentBlock(eSlime);
    ui->currentRBDisplay->setIcon(ui->eSlimeBtn->icon());
}

void MapBuilderWindow::on_ePokerBtn_clicked()
{
    scene->setCurrentBlock(ePoker);
    ui->currentRBDisplay->setIcon(ui->ePokerBtn->icon());
}

void MapBuilderWindow::on_eFlyBtn_clicked()
{
    scene->setCurrentBlock(eFly);
    ui->currentRBDisplay->setIcon(ui->eFlyBtn->icon());
}

void MapBuilderWindow::on_eSnailBtn_clicked()
{
    scene->setCurrentBlock(eSnail);
    ui->currentRBDisplay->setIcon(ui->eSnailBtn->icon());
}

#include "scene.h"

#include <QDebug>

#include <QPainter>
#include <QJsonDocument>
#include <QFontDatabase>

#include "physicsengine.h"
#include "rbodytype.h"
#include "interface.h"
#include "serialization.h"

#include "entities/genericmob.h"

Scene::Scene(QScrollBar *s, QObject *parent):QGraphicsScene(0, 0, 5000, 720, parent)
{
    scroll = s;

    // Liste des niveaux
    //    levels.append("/home/tom/qt-workspace/build-QtGame-Desktop-Debug/saves/slimeTest2.json");
    levels.append("://maps/level1.json");
    levels.append("://maps/level2.json");
    levels.append("://maps/level3.json");

    currentLevel = 0;

    startGame();

    // "Vue" de la scene ---> 5000 de long et 720 de haut
    setSceneRect(0, 0, 5000, 720);

    // Moteur physique
    new PhysicsEngine(this);

    // Gestion du son
    new SoundManager();
}

/**
 * "Démarre" le timer gérant le mouvement des mobs
 * TODO : démarrer l'IA au fur et à mesure que le joueur charge la map pour éviter les lags ?
 */
void Scene::startMobs(bool b)
{
    QList<QGraphicsItem*> items = this->items(sceneRect());
    for(QGraphicsItem *item: items) {
        if(item->type() == QGraphicsItem::UserType + 5) {
            GenericMob *mob = static_cast<GenericMob*>(item);
            mob->hasAI(b);
        }
    }
}

void Scene::loadMap(QString path)
{
    // On reset le niveau actuel
    QList<QGraphicsItem*> list = items(sceneRect());
    for(QGraphicsItem *item : list) {
        delete item;
    }

    QFile loadFile(path);

    if(!loadFile.open(QIODevice::ReadOnly)) {
        qDebug() << "IMPOSSIBLE D'OUVRIR LE LEVEL " << path;
        exit(0);
    }

    QByteArray loadData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));

    Serialization::loadMap(loadDoc, this);

    loadFile.close();

    startMobs(true);

    QTimer::singleShot(10, this, SLOT(moveScrollbar()));

}

/**
 * Event déclanché à chaque mouvement de souris
 * Change la position du curseur et refresh l'affichage à cet endroit
 */
void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF pos = mouseEvent->scenePos();
    cursor = QPointF(((int)pos.x() / 48) * 48, ((int)pos.y() / 48) * 48);
    update(QRectF(cursor.x()-48, cursor.y()-48, 144, 144));
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

/**
 * Event déclanché à chaque clic de souris
 * Pose un bloc sur la map
 */
void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Si le joueur est mort, qu'il a fini le niveau ou qu'il n'a pas de boites
    if(dead || levelFinished || player->getBoxes() == 0) {
        return;
    }

    if(event->button() == Qt::RightButton) {
        QPointF pos = event->scenePos();

        // Impossible de poser une caisse autre que dans l'air, l'eau ou la lave
        QList<QGraphicsItem*> list = items(pos);
        for(QGraphicsItem *item : list) {
            RigidBody *rb = qgraphicsitem_cast<RigidBody*>(item);
            if(rb->getType() != tWater && rb->getType() != tLava) {
                return;
            }
        }

        QPointF newPos(((int)pos.x() / 48) * 48, ((int)pos.y() / 48) * 48);

        RigidBody *rb = createRigidBody(tBoxEmpty);
        addItem(rb);

        rb->setPos(rb->mapFromScene(newPos));

        player->setBoxes(player->getBoxes() - 1);
        update(scroll->value()+1065, 0, 70, 70);      // On update le HUD
    }

    QGraphicsScene::mousePressEvent(event);
}

/**
 * Event déclanché à chaque pression de touche
 * Gère les déplacements du joueur
 */
void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) {   // On ignore les event à part le tout premier
        return;
    }
    switch(event->key())
    {
    case Qt::Key_D:         if(!(dead || levelFinished)) player->addDirection(1);   break;  // Droite
    case Qt::Key_Q:         if(!(dead || levelFinished)) player->addDirection(-1);  break;  // Gauche
    case Qt::Key_Space:     dead || levelFinished ? startGame() : player->jump();   break;  // Saut ou Try Again
    }
    QGraphicsScene::keyPressEvent(event);
}

/**
 * Event déclanché à chaque relachement de touche
 * Gère les déplacement du joueur
 */
void Scene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) {
        return;
    }
    switch(event->key()) {
    case Qt::Key_D:         if(!(dead || levelFinished)) player->addDirection(-1);   break;
    case Qt::Key_Q:         if(!(dead || levelFinished)) player->addDirection(1);    break;
    }
    QGraphicsScene::keyReleaseEvent(event);
}

/**
 * Dessine le HUD
 * TODO: charger les pixmaps à l'avance pour économiser du temps de calcul ?
 */
void Scene::drawForeground(QPainter *painter, const QRectF &rect)
{
    int v = scroll->value();

    int id = QFontDatabase::addApplicationFont(":/fonts/ressources/Fonts/ChickenPie.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont chickenPie(family);
    chickenPie.setPixelSize(48);

    QPointF mid(v, 360);

    // Affichage du foreground si le joueur est mort
    if(dead)
    {
        // Filtre gris
        QRadialGradient gradient(mid.x()+640, mid.y(), 1280);
        gradient.setColorAt(0, QColor::fromRgbF(0, 0, 0, 0.9));
        gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0.2));
        QBrush brush(gradient);
        painter->setBrush(brush);
        painter->drawRect(sceneRect());

        // Texte "Game over"
        chickenPie.setPixelSize(48);
        painter->setPen(Qt::white);
        painter->setFont(chickenPie);
        painter->drawText(QRect(mid.x(), mid.y()-60, 1280, 50), Qt::AlignCenter, "GAME OVER");
        chickenPie.setPixelSize(36);
        painter->setFont(chickenPie);
        painter->drawText(QRect(mid.x(), mid.y(), 1280, 50), Qt::AlignCenter, "Press [ Space ] to try again!");
        return;
    }
    // Affichage du foreground si le joueur a fini le niveau
    else if(levelFinished)
    {
        // Filtre gris
        QRadialGradient gradient(mid.x()+640, mid.y(), 1280);
        gradient.setColorAt(0, QColor::fromRgbF(0, 0, 0, 0.9));
        gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0.2));
        QBrush brush(gradient);
        painter->setBrush(brush);
        painter->drawRect(sceneRect());

        // Texte "Game over"
        chickenPie.setPixelSize(48);
        painter->setPen(Qt::white);
        painter->setFont(chickenPie);
        painter->drawText(QRect(mid.x(), mid.y()-60, 1280, 50), Qt::AlignCenter, "LEVEL "+QString::number(currentLevel)+" FINISHED");
        chickenPie.setPixelSize(36);
        painter->setFont(chickenPie);
        painter->drawText(QRect(mid.x(), mid.y(), 1280, 50), Qt::AlignCenter, "Press [SPACE] to go to the next level!");
        return;
    }
    // Affichage du curseur et du HUD
    else
    {
        // Affichage du curseur
        if(player->getBoxes() > 0)
        {
            QPixmap box(":/tiles/ressources/Tiles/box.png");
            painter->setOpacity(0.2f);
            painter->drawPixmap(cursor.x(), cursor.y(), 48, 48, box);
        }
        // Affichage du HUD
        if(rect.top() <= 70)
        {
            painter->setOpacity(1.0f);
            QPixmap heart(":/hud/ressources/HUD/hud_heartFull.png");
            QPixmap heartEmpty(":/hud/ressources/HUD/hud_heartEmpty.png");
            QPixmap coin(":/hud/ressources/HUD/hud_coins.png");
            QPixmap box(":/tiles/ressources/Tiles/box.png");

            QPixmap zero(":/hud/ressources/HUD/hud_0.png");
            QPixmap one(":/hud/ressources/HUD/hud_1.png");
            QPixmap two(":/hud/ressources/HUD/hud_2.png");
            QPixmap three(":/hud/ressources/HUD/hud_3.png");
            QPixmap four(":/hud/ressources/HUD/hud_4.png");
            QPixmap five(":/hud/ressources/HUD/hud_5.png");
            QPixmap six(":/hud/ressources/HUD/hud_6.png");
            QPixmap seven(":/hud/ressources/HUD/hud_7.png");
            QPixmap height(":/hud/ressources/HUD/hud_8.png");
            QPixmap nine(":/hud/ressources/HUD/hud_9.png");

            // Affichage de la vie du joueur
            if(player->getHealth() == 0) {
                painter->drawPixmap(v+10, 20, heartEmpty);
                painter->drawPixmap(v+70, 20, heartEmpty);
                painter->drawPixmap(v+130, 20, heartEmpty);
            }
            if(player->getHealth() == 1) {
                painter->drawPixmap(v+10, 20, heart);
                painter->drawPixmap(v+70, 20, heartEmpty);
                painter->drawPixmap(v+130, 20, heartEmpty);
            }
            else if(player->getHealth() == 2) {
                painter->drawPixmap(v+10, 20, heart);
                painter->drawPixmap(v+70, 20, heart);
                painter->drawPixmap(v+130, 20, heartEmpty);
            }
            else if(player->getHealth() == 3) {
                painter->drawPixmap(v+10, 20, heart);
                painter->drawPixmap(v+70, 20, heart);
                painter->drawPixmap(v+130, 20, heart);
            }

            // Affichage du nombre de pièces
            painter->drawPixmap(v+1140, 20, 47, 47, coin);

            int dizaines = (int)(player->getCoins()/10);
            switch(dizaines) {
            case 0: painter->drawPixmap(v+1200, 25, 28, 38, zero); break;
            case 1: painter->drawPixmap(v+1200, 25, 28, 38, one); break;
            case 2: painter->drawPixmap(v+1200, 25, 28, 38, two); break;
            case 3: painter->drawPixmap(v+1200, 25, 28, 38, three); break;
            case 4: painter->drawPixmap(v+1200, 25, 28, 38, four); break;
            case 5: painter->drawPixmap(v+1200, 25, 28, 38, five); break;
            case 6: painter->drawPixmap(v+1200, 25, 28, 38, six); break;
            case 7: painter->drawPixmap(v+1200, 25, 28, 38, seven); break;
            case 8: painter->drawPixmap(v+1200, 25, 28, 38, height); break;
            case 9: painter->drawPixmap(v+1200, 25, 28, 38, nine); break;
            }
            switch (player->getCoins() - dizaines*10) {
            case 0: painter->drawPixmap(v+1235, 25, 28, 38, zero); break;
            case 1: painter->drawPixmap(v+1235, 25, 28, 38, one); break;
            case 2: painter->drawPixmap(v+1235, 25, 28, 38, two); break;
            case 3: painter->drawPixmap(v+1235, 25, 28, 38, three); break;
            case 4: painter->drawPixmap(v+1235, 25, 28, 38, four); break;
            case 5: painter->drawPixmap(v+1235, 25, 28, 38, five); break;
            case 6: painter->drawPixmap(v+1235, 25, 28, 38, six); break;
            case 7: painter->drawPixmap(v+1235, 25, 28, 38, seven); break;
            case 8: painter->drawPixmap(v+1235, 25, 28, 38, height); break;
            case 9: painter->drawPixmap(v+1235, 25, 28, 38, nine); break;
            }

            // Affichage du nombre de caisses
            painter->drawPixmap(v+1005, 20, 47, 47, box);

            dizaines = (int)(player->getBoxes()/10);
            switch(dizaines) {
            case 0: painter->drawPixmap(v+1065, 25, 28, 38, zero); break;
            case 1: painter->drawPixmap(v+1065, 25, 28, 38, one); break;
            case 2: painter->drawPixmap(v+1065, 25, 28, 38, two); break;
            case 3: painter->drawPixmap(v+1065, 25, 28, 38, three); break;
            case 4: painter->drawPixmap(v+1065, 25, 28, 38, four); break;
            case 5: painter->drawPixmap(v+1065, 25, 28, 38, five); break;
            case 6: painter->drawPixmap(v+1065, 25, 28, 38, six); break;
            case 7: painter->drawPixmap(v+1065, 25, 28, 38, seven); break;
            case 8: painter->drawPixmap(v+1065, 25, 28, 38, height); break;
            case 9: painter->drawPixmap(v+1065, 25, 28, 38, nine); break;
            }
            switch (player->getBoxes() - dizaines*10) {
            case 0: painter->drawPixmap(v+1100, 25, 28, 38, zero); break;
            case 1: painter->drawPixmap(v+1100, 25, 28, 38, one); break;
            case 2: painter->drawPixmap(v+1100, 25, 28, 38, two); break;
            case 3: painter->drawPixmap(v+1100, 25, 28, 38, three); break;
            case 4: painter->drawPixmap(v+1100, 25, 28, 38, four); break;
            case 5: painter->drawPixmap(v+1100, 25, 28, 38, five); break;
            case 6: painter->drawPixmap(v+1100, 25, 28, 38, six); break;
            case 7: painter->drawPixmap(v+1100, 25, 28, 38, seven); break;
            case 8: painter->drawPixmap(v+1100, 25, 28, 38, height); break;
            case 9: painter->drawPixmap(v+1100, 25, 28, 38, nine); break;
            }
        }
    }
}

/**
 * Fonction appelée à la mort du joueur
 */
void Scene::gameover()
{
    if(dead) {
        return;
    }

    dead = true;
    removeItem(player);
    delete player;

    startMobs(false);

    SoundManager::playSound(sGameover);

    update(sceneRect());
}

/**
 * Fonction appelée à la fin d'un niveau
 */
void Scene::levelComplete()
{
    if(levelFinished) {
        return;
    }

    levelFinished = true;
    removeItem(player);
    delete player;
    currentLevel++;

    SoundManager::playSound(sLevelWin);

    startMobs(false);

    update(sceneRect());

    if(currentLevel == 3) { // Si il a fini le jeu
        // Credits
    }
}

/**
 * Fonction appelée au début d'un niveau
 */
void Scene::startGame()
{
    dead = false;
    levelFinished = false;

    // Chargement du level
    loadMap(levels.at(currentLevel));

    // Création du joueur
    player = new Player();
    addItem(player);
    player->setPos(25, 600);
    player->fall();

    // Gestion de l'interface
    Interface *interface = new Interface(this, player, scroll);
    connect(player, &Player::playerMoved, interface, &Interface::moveInterface);
    connect(player, &Player::statsChanged, interface, &Interface::updateHUD);
}

void Scene::moveScrollbar()
{
    scroll->setValue(0);
    update(sceneRect());
}



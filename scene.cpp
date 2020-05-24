#include "scene.h"

#include <QDebug>
#include <QPointF>
#include <QPainter>
#include <QPushButton>
#include <QGraphicsProxyWidget>

#include "physicsengine.h"
#include "rbodytype.h"
#include "interface.h"

#include "entities/genericmob.h"
#include "entities/coingold.h"

Scene::Scene(QScrollBar *s, QObject *parent):QGraphicsScene(0, 0, 8000, 720, parent)
{
    scroll = s;

    // Placement d'un bloc au sol sous le joueur
    RigidBody *rb1 = new RigidBody();
    addItem(rb1);
    rb1->setPos(0, 672);
    RigidBody *rb2 = new RigidBody();
    addItem(rb2);
    rb2->setPos(48, 672);

    player = new Player();
    addItem(player);
    player->setLastPlatform(rb1);
    player->setPos(25, 672 - player->boundingRect().height());

    // "Vue" de la scene ---> 8000 de long et 720 de haut
    setSceneRect(0, 0, 8000, 720);

    dead = false;

    // Gestion du son dans la scène
    new SoundManager();

    // Moteur physique instancié avec la scène
    PhysicsEngine* engine = new PhysicsEngine(this);
    Q_UNUSED(engine)

    this->installEventFilter(this);

    // Gestion de l'interface
    Interface *interface = new Interface(this, player, scroll);

    connect(player, &Player::playerMoved, interface, &Interface::moveInterface);
    connect(player, &Player::statsChanged, interface, &Interface::updateHUD);
}

/**
 * "Démarre" le timer gérant le mouvement des mobs
 * TODO : démarrer l'IA au fur et à mesure que le joueur charge la map pour éviter les lags ?
 */
void Scene::startMobs()
{
    QList<QGraphicsItem*> items = this->items(sceneRect());
    for(QGraphicsItem *item: items) {
        if(item->type() == QGraphicsItem::UserType + 5) {
            GenericMob *mob = static_cast<GenericMob*>(item);
            mob->hasAI(true);
        }
    }
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
    if(dead || player->getBoxes() == 0) {
        return;
    }

    if(event->button() == Qt::RightButton) {
        QPointF pos = event->scenePos();
        QPointF newPos(((int)pos.x() / 48) * 48, ((int)pos.y() / 48) * 48);

        RigidBody *rb = createRigidBody(tBoxEmpty);
        addItem(rb);

        rb->setPos(rb->mapFromScene(newPos));

        player->setBoxes(player->getBoxes() - 1);
        update(scroll->value(), 0, 1280, 100);
    }

    QGraphicsScene::mousePressEvent(event);
}

/**
 * Récupère uniquement les events du clavier pour gérer les déplacements du joueurs
 */
bool Scene::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);

    if(dead) {
        return false;
    }

    // Si une touche est pressée
    if(event->type() == QEvent::KeyPress) {
        if(((QKeyEvent*)event)->isAutoRepeat()) {   // On ignore les event à part le tout premier
            return false;
        }
        int key = ((QKeyEvent*)event)->key();
        switch(key) {
        case Qt::Key_D:         player->addDirection(1);    break;  // Droite
        case Qt::Key_Q:         player->addDirection(-1);   break;  // Gauche
        case Qt::Key_Space:     player->jump();             break;  // Saut
        }
    }

    // Si une touche est relachée, on stop le mouvement
    else if(event->type() == QEvent::KeyRelease) {
        if(((QKeyEvent*)event)->isAutoRepeat()) {
            return false;
        }
        int key = ((QKeyEvent*)event)->key();
        switch(key) {
        case Qt::Key_D:         player->addDirection(-1);   break;
        case Qt::Key_Q:         player->addDirection(1);    break;
        }
    }

    return false;
}

/**
 * Dessine le HUD
 * TODO: charger les pixmaps à l'avance pour économiser du temps de calcul
 */
void Scene::drawForeground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    int v = scroll->value();

    // Affichage du filtre coloré si le joueur est mort
    if(dead) {
//        QBrush brush(QColor(0, 0, 0));
//        painter->setBrush(brush);
//        painter->setOpacity(0.5f);
//        painter->drawRect(sceneRect());
        return;
    }
    else {
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

        // Affichage le curseur
        if(player->getBoxes() > 0) {
            painter->setOpacity(0.2f);
            painter->drawPixmap(cursor.x(), cursor.y(), 48, 48, box);
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
    delete player;

    SoundManager::playSound(sGameover);

    QPushButton *btn = new QPushButton("Try again");
    btn->setGeometry(0, 0, 200, 50);
    QGraphicsProxyWidget *widget = addWidget(btn);

    widget->setPos(scroll->value()+540, 360);

    update(sceneRect());
}

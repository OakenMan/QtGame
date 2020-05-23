#include "scene.h"

#include <QDebug>
#include <QPointF>
#include <QPainter>

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

    scroll->setValue(0);

    // Gestion du son dans la scène
    new SoundManager();

    // Moteur physique instancié avec la scène
    PhysicsEngine* engine = new PhysicsEngine(this);
    Q_UNUSED(engine)

    this->installEventFilter(this);

    // Gestion de l'interface
    new Interface(this, player, scroll);
}

void Scene::startMobs()
{
    QList<QGraphicsItem*> items = this->items(sceneRect());
    for(QGraphicsItem *item: items) {
        RigidBody *rb = static_cast<RigidBody*>(item);
        if(rb->type() == QGraphicsItem::UserType + 5) {
            GenericMob *mob = static_cast<GenericMob*>(item);
            mob->hasAI(true);
        }
    }
}

/**
 * @brief Event déclanché à chaque clic de souris (actuellement utilisé pour placer des blocs, à supprimer plus tard)
 */
void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton) {
        QPointF pos = event->scenePos();
        QPointF newPos(((int)pos.x() / 48) * 48, ((int)pos.y() / 48) * 48);

        RigidBody *rb = new RigidBody();
        addItem(rb);

        rb->setPos(rb->mapFromScene(newPos));
        rb->setFlags(QGraphicsItem::ItemIsMovable);
    }
    QGraphicsScene::mousePressEvent(event);
}

bool Scene::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);

    // Si une touche est pressée
    if(event->type() == QEvent::KeyPress) {
        if(((QKeyEvent*)event)->isAutoRepeat()) {   // On ignore les event à part le tout premier
            return false;
        }
        int key = ((QKeyEvent*)event)->key();
        switch(key) {
        case Qt::Key_D:                     // Droite
            player->addDirection(1);
            break;
        case Qt::Key_Q:                     // Gauche
            player->addDirection(-1);
            break;
        case Qt::Key_Space:                 // Saut
            player->jump();
            break;
        }
    }
    // Si une touche est relachée, on stop le mouvement
    else if(event->type() == QEvent::KeyRelease) {
        if(((QKeyEvent*)event)->isAutoRepeat()) {
            return false;
        }
        int key = ((QKeyEvent*)event)->key();
        switch(key) {
        case Qt::Key_D:
            player->addDirection(-1);
            break;
        case Qt::Key_Q:
            player->addDirection(1);
            break;
        }
    }
    return false;
}

void Scene::drawForeground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    QPixmap heart(":/hud/ressources/HUD/hud_heartFull.png");
    QPixmap heartEmpty(":/hud/ressources/HUD/hud_heartEmpty.png");
    painter->drawPixmap(10, 20, heart);
    painter->drawPixmap(70, 20, heart);
    painter->drawPixmap(130, 20, heartEmpty);

    QPixmap coin(":/hud/ressources/HUD/hud_coins.png");
    painter->drawPixmap(1140, 20, 47, 47, coin);

    QPixmap zero(":/hud/ressources/HUD/hud_0.png");
    painter->drawPixmap(1200, 25, 28, 38, zero);
    painter->drawPixmap(1235, 25, 28, 38, zero);

    QPixmap box(":/tiles/ressources/Tiles/box.png");
    painter->drawPixmap(1005, 20, 47, 47, box);

    painter->drawPixmap(1065, 25, 28, 38, zero);
    painter->drawPixmap(1100, 25, 28, 38, zero);
}

void Scene::gameover()
{
    delete player;
    SoundManager::playSound(sGameover);
    setForegroundBrush(QColor(0, 0, 0, 127));
}

#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QScrollBar>

#include "player.h"
#include "soundmanager.h"

/**
 * La scène, là où tout se passe tmtc
 */
class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit Scene(QScrollBar *s, QObject *parent=nullptr);

    void startMobs(bool b);
    void loadMap(QString path);

protected:
    /* SURCHARGES DES EVENTS */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    void drawForeground(QPainter *painter, const QRectF &rect);

public slots:
    void startGame();
    void gameover();
    void levelComplete();
    void moveScrollbar();

private:
    Player * player;        // Joueur

    QStringList levels;     // Liste des niveaux
    int currentLevel;       // Id du niveau actuel

    QScrollBar *scroll;     // Scrollbar horizontale
    QPointF cursor;         // Position du curseur

    bool dead;              // Assez explicite
    bool levelFinished;     // Idem

};

#endif // SCENE_H

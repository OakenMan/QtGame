#ifndef PLAYER_H
#define PLAYER_H

#include <QPropertyAnimation>
#include <QEasingCurve>

#include "entities/entity.h"

/**
 * Le joueur (c'est toi!)
 */
class Player : public Entity
{
    Q_OBJECT
    Q_PROPERTY(qreal jumpFactor READ getJumpFactor WRITE setJumpFactor NOTIFY jumpFactorChanged)

public:
    Player();
    ~Player();

    /* SURCHARGES */
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

    /* GETTERS ET SETTERS */
    int getDirection() const;                           // Pour gérer les déplacements
    void addDirection(const int direction);             // du joueur

    qreal getJumpFactor() const;                        // Utilisée uniquement par
    void setJumpFactor(const qreal &newJumpFactor);     // l'animation de saut

    void setLastPlatform(QGraphicsItem *item);          // Utilisée uniquement au lancement du jeu

    bool isFalling();

    int getHealth();
    int getCoins();
    int getBoxes();

    void setBoxes(int boxes);

public slots:
    /* Ces méthodes changent le state et l'animation du joueur,
     * puis déclanchent les timers correspondant à l'action */
    void stand();
    void jump();
    void walk();
    void fall();

private slots:
    /* Ces méthodes sont appelée par des signaux et gèrent
     * les mouvements du joueur */
    void movePlayer();
    void jumpPlayer();
    void fallPlayer();
    void checkTimer();

signals:
    void jumpFactorChanged(qreal);  // Signal émit par l'animation de saut lorsque jumpFactor change
    void playerMoved(int);          // Signal émit lorsque le joueur bouge
    void statsChanged();            // Signal émit lorsque les stats du joueur changent

private:
    const int velocity = 7;         // Vitesse
    const int jumpHeight = 140;     // Hauteur de saut

    enum State {                    // État actuel
        Standing = 0,
        Walking,
        Jumping,
        Falling
    };
    State state;

    int direction;                  // Direction (-1=gauche, 0=immobile, 1=droite)

    // Stats
    int health;
    int coins;
    int boxes;

    // Sprites
    QPixmap walkPixmap;
    QPixmap standPixmap;
    QPixmap jumpPixmap;
    QPixmap hurtPixmap;
    QPixmap walk1, walk2, walk3, walk4, walk5, walk6, walk7, walk8, walk9, walk10, walk11;

    int walkFrame;  // Numéro de la frame actuel de l'animation de marche

    bool dead;      // Assez explicite...

    // Gestion de l'animation de saut
    QPropertyAnimation *jumpAnimation;
    qreal jumpFactor;

    // Timers pour le déplacement
    QTimer *moveTimer;
    QTimer *fallTimer;

    QGraphicsItem *lastPlatform;    // Dernière plateforme (utilisée pour savoir la hauteur d'un saut)
    const qreal groundLevel = 672;  // Hauteur du sol (vraiment nécessaire ?)

    /* MÉTHODES PRIVÉES */
    RigidBody * collidingPlatforms();
    void checkCollisions();

    void die();         // "Tue" le joueur

    void nextFrame();   // Change la frame de marche

    // Définition des hitboxes du joueur
    bool isTouchingFoot(QGraphicsItem *item);       // Renvoie true si les pieds du joueur touchent 'item' (utile pour tuer les mobs)
    bool isTouchingHead(QGraphicsItem *item);       // Renvoie true si la tête du joueur touche 'item' (utile pour casser les caisses)
    bool isTouchingPlatform(QGraphicsItem *item);   // Renvoie true si les pieds du joueur touchent 'item' (plus flexible, utile pour la chute)

};

#endif // PLAYER_H

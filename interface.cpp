#include "interface.h"

QScrollBar *Interface::scroll;
Scene * Interface::scene;
Player * Interface::player;

Interface::Interface(Scene *newScene, Player *newPlayer, QScrollBar *s)
{
    scroll = s;
    scene = newScene;
    player = newPlayer;
}

void Interface::moveInterface(int dx)
{
    // Différence de position entre le scroll et le joueur
    int diff = player->pos().x() - scroll->value();

    if(dx > 0) {

        // Si le joueur est à 800 pixels de la gauche de l'écran, on bouge l'écran
        if(diff > 800) {

            // (sauf si l'écran est déjà trop à droite)
            if(scroll->value() > 6720) {
                return;
            }

            scroll->setValue(scroll->value() + dx);
            updateHUD();
        }
    }
    else if(dx < 0) {
        if(diff < 480) {
            if(scroll->value() < 0) {
                return;
            }
            scroll->setValue(scroll->value() + dx);
            updateHUD();
        }
    }
}

void Interface::updateHUD()
{
    scene->update(scroll->value(), 0, 1280, 100);
}

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QMediaPlayer>
#include <QMediaContent>
#include <QMediaResource>
#include <QSoundEffect>

#include "soundeffect.h"

/**
 * Classe qui gère les effets sonores et les musiques.
 * Pour l'utiliser dans une autre classe :
 *  SoundManager sm = new SoundManager();
 *  sm->playSoundEffect(SoundEffect);
 * Liste des effets dans "soundeffect.h"
 */
class SoundManager: public QObject
{
    Q_OBJECT

public:
    explicit SoundManager(QWidget *parent = 0);
    ~SoundManager();

private:

    // Effets sonores
    QSoundEffect *jump;
    QSoundEffect *coin;
    QSoundEffect *gameover;
    QSoundEffect *powerup;

    // Musiques
    QMediaPlayer *music;

signals:
   void stopMusic();

public slots:
   void playSoundEffect(SoundEffect);
};

#endif // SOUNDMANAGER_H

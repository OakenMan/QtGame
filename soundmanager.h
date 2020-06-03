#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSoundEffect>

#include "soundeffect.h"

/**
 * Classe qui gère les effets sonores et les musiques.
 */
class SoundManager: public QObject
{
    Q_OBJECT

public:
    explicit SoundManager(QWidget *parent = 0);
    ~SoundManager();

    static void playSound(SoundEffect);
    static void stopMusic();
    static void setVolume(int volume);

private:

    // Effets sonores
    static QSoundEffect *jump;
    static QSoundEffect *coin;
    static QSoundEffect *gameover;
    static QSoundEffect *powerup;
    static QSoundEffect *healthPickup;
    static QSoundEffect *mobDie;
    static QSoundEffect *levelWin;
    static QSoundEffect *breakBox;
    static QSoundEffect *damage;

    // Musiques
    static QMediaPlaylist *musics;

    // Media Player
    static QMediaPlayer *mediaPlayer;
};

#endif // SOUNDMANAGER_H

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

    static void playSound(SoundEffect);

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
    static QMediaPlayer *level1;
    static QMediaPlayer *level2;
    static QMediaPlayer *level3;

//signals:
//   void stopMusic();

//public slots:
//   void playSoundEffect(SoundEffect);
};

#endif // SOUNDMANAGER_H

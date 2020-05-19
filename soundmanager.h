#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QMediaPlayer>
#include <QMediaContent>
#include <QMediaResource>
#include <QSoundEffect>

#include "soundeffect.h"

class SoundManager: public QObject
{
    Q_OBJECT

public:
    explicit SoundManager(QWidget *parent = 0);
    ~SoundManager();

private:

    QSoundEffect *jump;
    QSoundEffect *coin;
    QSoundEffect *gameover;
    QSoundEffect *powerup;
    // Autres effets ici

    QMediaPlayer *music;
    // Autres musiques ici

signals:
   void stopMusic();

public slots:
   void playSoundEffect(SoundEffect);
//   void playSoundEffect(QString);
};

#endif // SOUNDMANAGER_H

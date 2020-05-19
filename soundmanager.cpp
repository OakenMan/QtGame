#include "soundmanager.h"

SoundManager::SoundManager(QWidget *parent)
{
    jump = new QSoundEffect();
    jump->setSource(QUrl("qrc:/sounds/ressources/Sounds/jump.wav"));
    jump->setLoopCount(0);
    jump->setVolume(.25f);

    coin = new QSoundEffect();
    coin->setSource(QUrl("qrc:/sounds/ressources/Sounds/coin.wav"));
    coin->setLoopCount(0);
    coin->setVolume(.25f);

    gameover = new QSoundEffect();
    gameover->setSource(QUrl("qrc:/sounds/ressources/Sounds/gameOver.wav"));
    gameover->setLoopCount(0);
    gameover->setVolume(.25f);

    powerup = new QSoundEffect();
    powerup->setSource(QUrl("qrc:/sounds/ressources/Sounds/powerup.wav"));
    powerup->setLoopCount(0);
    powerup->setVolume(.25f);

    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/ressources/Sounds/music.mp3"));
}

SoundManager::~SoundManager()
{

}

//void SoundManager::playSoundEffect(QString effect) {

//}

void SoundManager::playSoundEffect(SoundEffect effect) {
    switch(effect) {
    case sJump:     jump->play();       break;
    case sCoin:     coin->play();       break;
    case sGameover: gameover->play();   break;
    case sPowerup:  powerup->play();    break;
    default:                            break;
    }
}

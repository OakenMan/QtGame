#include "soundmanager.h"

QSoundEffect * SoundManager::jump;
QSoundEffect * SoundManager::coin;
QSoundEffect * SoundManager::powerup;
QSoundEffect * SoundManager::gameover;
QSoundEffect * SoundManager::healthPickup;
QSoundEffect * SoundManager::mobDie;
QSoundEffect * SoundManager::levelWin;
QSoundEffect * SoundManager::breakBox;
QSoundEffect * SoundManager::damage;
QMediaPlaylist * SoundManager::musics;
QMediaPlayer * SoundManager::mediaPlayer;

SoundManager::SoundManager(QWidget *parent)
{
    Q_UNUSED(parent);

    jump = new QSoundEffect();
    jump->setSource(QUrl("qrc:/sounds/ressources/Sounds/jump.wav"));
    jump->setLoopCount(0);
    jump->setVolume(.25f);

    coin = new QSoundEffect();
    coin->setSource(QUrl("qrc:/sounds/ressources/Sounds/coin2.wav"));
    coin->setLoopCount(0);
    coin->setVolume(.25f);

    gameover = new QSoundEffect();
    gameover->setSource(QUrl("qrc:/sounds/ressources/Sounds/busted.wav"));
    gameover->setLoopCount(0);
    gameover->setVolume(1.0f);

    powerup = new QSoundEffect();
    powerup->setSource(QUrl("qrc:/sounds/ressources/Sounds/powerup.wav"));
    powerup->setLoopCount(0);
    powerup->setVolume(.25f);

    healthPickup = new QSoundEffect();
    healthPickup->setSource(QUrl("qrc:/sounds/ressources/Sounds/lifePickup.wav"));
    healthPickup->setLoopCount(0);
    healthPickup->setVolume(1.0f);

    mobDie = new QSoundEffect();
    mobDie->setSource(QUrl("qrc:/sounds/ressources/Sounds/powerup.wav"));
    mobDie->setLoopCount(0);
    mobDie->setVolume(.25f);

    levelWin = new QSoundEffect();
    levelWin->setSource(QUrl("qrc:/sounds/ressources/Sounds/levelWin2.wav"));
    levelWin->setLoopCount(0);
    levelWin->setVolume(1.0f);

    breakBox = new QSoundEffect();
    breakBox->setSource(QUrl("qrc:/sounds/ressources/Sounds/powerup.wav"));
    breakBox->setLoopCount(0);
    breakBox->setVolume(.25f);

    damage = new QSoundEffect();
    damage->setSource(QUrl("qrc:/sounds/ressources/Sounds/oof.wav"));
    damage->setLoopCount(0);
    damage->setVolume(.50f);

    musics = new QMediaPlaylist();
    musics->addMedia(QUrl("qrc:/sounds/ressources/Sounds/mii-channel.wav"));
    musics->addMedia(QUrl("qrc:/sounds/ressources/Sounds/music.mp3"));
    musics->addMedia(QUrl("qrc:/sounds/ressources/Sounds/doom-ost.mp3"));
    musics->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

    mediaPlayer = new QMediaPlayer();
    mediaPlayer->setPlaylist(musics);
    mediaPlayer->setAudioRole(QAudio::GameRole);
    mediaPlayer->setVolume(75);
}

SoundManager::~SoundManager()
{

}

void SoundManager::playSound(SoundEffect effect)
{
    switch(effect) {
    case mLevel1:       musics->setCurrentIndex(0); mediaPlayer->play(); break;
    case mLevel2:       musics->setCurrentIndex(1); mediaPlayer->play(); break;
    case mLevel3:       musics->setCurrentIndex(2); mediaPlayer->play(); break;
    case sJump:         jump->play();           break;
    case sCoin:         coin->play();           break;
    case sGameover:     gameover->play();       break;
    case sPowerup:      powerup->play();        break;
    case sHealthPickup: healthPickup->play();   break;
    case sMobDie:       mobDie->play();         break;
    case sLevelWin:     levelWin->play();       break;
    case sBreakBox:     breakBox->play();       break;
    case sDamage:       damage->play();         break;
    default:            mediaPlayer->stop();    break;
    }
}

void SoundManager::stopMusic()
{
    mediaPlayer->stop();
}

void SoundManager::setVolume(int volume)
{
    mediaPlayer->setVolume(volume);
}

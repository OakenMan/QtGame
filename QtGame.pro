#-------------------------------------------------
#
# Project created by QtCreator 2020-05-16T16:39:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtGame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    scene.cpp \
    player.cpp \
    rigidbody.cpp \
    mapbuilderwindow.cpp \
    mapbuilder.cpp \
    blocks/solidbrick.cpp \
    blocks/platformbrick.cpp \
    blocks/bonusbox.cpp \
    blocks/groundbrick.cpp \
    serialization.cpp \
    tiles/tile.cpp \
    tiles/genericplatform.cpp \
    tiles/grassplatform.cpp \
    tiles/dirtplatform.cpp \
    tiles/stoneplatform.cpp \
    tiles/sandplatform.cpp \
    tiles/snowplatform.cpp \
    tiles/castleplatform.cpp \
    tiles/water.cpp \
    tiles/lava.cpp \
    tiles/boxcoin.cpp \
    tiles/boxitem.cpp \
    tiles/box.cpp \
    tiles/boxalt.cpp \
    tiles/boxempty.cpp \
    entities/entity.cpp \
    entities/coinbronze.cpp \
    entities/coinsilver.cpp \
    entities/coingold.cpp \
    tiles/signexit.cpp \
    tiles/signleft.cpp \
    tiles/signright.cpp

HEADERS += \
        mainwindow.h \
    scene.h \
    player.h \
    rigidbody.h \
    mapbuilderwindow.h \
    mapbuilder.h \
    blocks.h \
    blocks/solidbrick.h \
    blocks/platformbrick.h \
    blocks/bonusbox.h \
    blocks/groundbrick.h \
    serialization.h \
    tiles/tile.h \
    tiles/genericplatform.h \
    tiles/grassplatform.h \
    rbodytype.h \
    tiles/dirtplatform.h \
    tiles/stoneplatform.h \
    tiles/sandplatform.h \
    tiles/snowplatform.h \
    tiles/castleplatform.h \
    tiles/water.h \
    tiles/lava.h \
    tiles/boxcoin.h \
    tiles/boxitem.h \
    tiles/box.h \
    tiles/boxalt.h \
    tiles/boxempty.h \
    entities/entity.h \
    entities/coinbronze.h \
    entities/coinsilver.h \
    entities/coingold.h \
    tiles/signexit.h \
    tiles/signleft.h \
    tiles/signright.h

FORMS += \
        mainwindow.ui \
    mapbuilderwindow.ui

RESOURCES += \
    ressources.qrc

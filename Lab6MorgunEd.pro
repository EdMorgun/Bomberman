#-------------------------------------------------
#
# Project created by QtCreator 2018-12-13T16:45:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab6MorgunEd
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    balloon.cpp \
    bomb.cpp \
    bomberman.cpp \
    game.cpp \
    unit.cpp \
    drawunit.cpp \
    physicalunit.cpp \
    factorybomber.cpp \
    factoryballoon.cpp \
    doors.cpp \
    statedoors.cpp \
    doorsclosed.cpp \
    doorsoppened.cpp

HEADERS += \
        mainwindow.h \
    balloon.h \
    bomb.h \
    bomberman.h \
    drawableobject.h \
    game.h \
    physicalobject.h \
    unit.h \
    drawunit.h \
    explosionarea.h \
    physicalunit.h \
    factory.h \
    factory.h \
    factorybomber.h \
    factoryballoon.h \
    doors.h \
    state.h \
    doorsclosed.h \
    doorsoppened.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

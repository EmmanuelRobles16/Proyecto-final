QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialogoretro.cpp \
    enemigovolador.cpp \
    esferadragon.cpp \
    goku.cpp \
    hud.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    metafinal.cpp \
    personaje.cpp \
    plataforma.cpp \
    proyectil.cpp \
    tenshinhan.cpp

HEADERS += \
    dialogoretro.h \
    enemigovolador.h \
    esferadragon.h \
    goku.h \
    hud.h \
    mainwindow.h \
    menu.h \
    metafinal.h \
    personaje.h \
    plataforma.h \
    proyectil.h \
    tenshinhan.h

FORMS += \
    mainwindow.ui \
    menu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

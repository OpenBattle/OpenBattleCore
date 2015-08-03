#-------------------------------------------------
#
# Project created by QtCreator 2015-08-02T22:01:27
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = OpenBattleCore
TEMPLATE = lib

DEFINES += QT
DEFINES += OPENBATTLECORE_LIBRARY

SOURCES += \
    Protocol.cpp \
    Serializer.cpp

HEADERS +=\
    Array.h \
    Generated.h \
    global.h \
    Message.h \
    OpenBattleCore.h \
    Protocol.h \
    Serializer.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

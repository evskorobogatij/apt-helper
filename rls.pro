#-------------------------------------------------
#
# Project created by QtCreator 2012-06-25T22:37:41
#
#-------------------------------------------------

DESTDIR = bin

QT       += core gui widgets sql

TARGET = rls
#CONFIG   += console

TEMPLATE = app

SOURCES += main.cpp \
    qmdcontroler.cpp \
    qmdwindow.cpp \
    qmdbase.cpp \
    qmdsettings.cpp

HEADERS += \
    qmdcontroler.h \
    qmdwindow.h \
    qmdbase.h \
    qmdrlsitem.h \
    qmdsettings.h

FORMS += \
    qmdwindow.ui

OTHER_FILES += \
    stile.qss

RESOURCES += \
    res.qrc

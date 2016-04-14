#-------------------------------------------------
#
# Project created by QtCreator 2016-03-17T18:08:23
#
#-------------------------------------------------

QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab1dot2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    drawwidget.cpp \
    controlpanelwidget.cpp \
    circle.cpp \
    config.cpp  \
    canvas.cpp

HEADERS  += mainwindow.h \
    drawwidget.h \
    controlpanelwidget.h \
    circle.h \
    config.h  \
    canvas.h

CONFIG += c++11

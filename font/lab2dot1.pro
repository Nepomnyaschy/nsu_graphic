#-------------------------------------------------
#
# Project created by QtCreator 2016-04-15T02:06:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab2dot1
TEMPLATE = app


SOURCES += main.cpp\
    font.cpp \
    glyph.cpp \
    mainwindow.cpp \
    canvas.cpp \
    config.cpp \
    controlpanelwidget.cpp \
    drawwidget.cpp \
    point.cpp \
    coordinatesystem.cpp

HEADERS  += mainwindow.h \
    font.h \
    glyph.h \
    canvas.h \
    config.h \
    controlpanelwidget.h \
    drawwidget.h \
    point.h \
    coordinatesystem.h

CONFIG += c++11

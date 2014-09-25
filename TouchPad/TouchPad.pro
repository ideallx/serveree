#-------------------------------------------------
#
# Project created by QtCreator 2014-09-24T12:50:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TouchPad
TEMPLATE = app

CONFIG += c++11

SOURCES  += main.cpp\
            LayerUI\mainwindow.cpp \
            LayerUI\myscene.cpp \
            LayerUI\myview.cpp \

HEADERS  += LayerUI\mainwindow.h \
            LayerUI\myscene.h \
            LayerUI\myview.h \

FORMS    += mainwindow.ui

INCLUDEPATH += include
INCLUDEPATH += LayerUI

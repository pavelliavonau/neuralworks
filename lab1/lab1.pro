#-------------------------------------------------
#
# Project created by QtCreator 2012-12-27T21:38:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab1
TEMPLATE = app

#CONFIG += debug

SOURCES += main.cpp\
        Main_Window.cpp \
    logic/matrix.cpp

HEADERS  += Main_Window.h \
    logic/matrix.h

FORMS    += Main_Window.ui

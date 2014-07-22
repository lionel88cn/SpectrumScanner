#-------------------------------------------------
#
# Project created by QtCreator 2014-07-22T11:31:01
#
#-------------------------------------------------
include  (qwt.pri)
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpectrumScanner
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    plot.cpp

HEADERS  += mainwindow.h \
    plot.h

FORMS    += mainwindow.ui

#-------------------------------------------------
#
# Project created by QtCreator 2014-07-22T11:31:01
#
#-------------------------------------------------
macx{
    include  (/usr/local/qwt-6.1.0/features/qwt.prf)
    QMAKE_LFLAGS += -F/Library/Frameworks
    LIBS += -framework nidaqmxbase
    LIBS += -framework nidaqmxbaselv
}
win32:include (C:/Qwt-6.1.0/features/qwt.prf)
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpectrumScanner
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    plot.cpp \
    controlpannel.cpp \
    DAQManager.cpp \
    Executor.cpp \
    MessageWindow.cpp \
    MotorControlPannel.cpp

HEADERS  += mainwindow.h \
    plot.h \
    controlpannel.h \
    DAQManager.h \
    Executor.h \
    MessageWindow.h \
    MotorControlPannel.h \
    NIDAQmxBase.h

FORMS    +=

#-------------------------------------------------
#
# Project created by QtCreator 2019-05-06T14:33:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pen_test
TEMPLATE = app

SOURCES += main.cpp\
        penwindow.cpp \
    openglwidget.cpp \
    view.cpp \
    scene.cpp \
    pensetwidget.cpp \
    commonfunc.cpp \
    additemthread.cpp \
    items.cpp \
    edgeblureffect.cpp \
    itemgroup.cpp \
    stackedwidget.cpp

HEADERS  += penwindow.h \
    openglwidget.h \
    view.h \
    scene.h \
    pensetwidget.h \
    commonfunc.h \
    additemthread.h \
    items.h \
    edgeblureffect.h \
    itemgroup.h \
    stackedwidget.h

FORMS    += penwindow.ui \
    pensetwidget.ui

TEMPLATE = app
CONFIG += console c++14
#CONFIG -= app_bundle
#CONFIG -= qt

QT += widgets gui core

SOURCES += main.cpp \
    grid.cpp \
    gameoflifepixmap.cpp \
    mywindow.cpp

HEADERS += \
    grid.h \
    gameoflifepixmap.h \
    mywindow.h

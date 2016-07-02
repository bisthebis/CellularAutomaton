TEMPLATE = app
CONFIG += console c++14
#CONFIG -= app_bundle
#CONFIG -= qt

QT += widgets gui core

SOURCES += main.cpp \
    grid.cpp \
    gridwidget.cpp

HEADERS += \
    grid.h \
    gridwidget.h

#-------------------------------------------------
#
# Project created by QtCreator 2012-10-03T20:25:19
#
#-------------------------------------------------

QT       += core gui

TARGET = GK
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    paintarea.cpp \
    Graphics/graphics.cpp \
    Graphics/line.cpp \
    Graphics/polygon.cpp \
    Graphics/colors.cpp \
    Graphics/octree.cpp \
    Graphics/colorquantizer.cpp

HEADERS  += mainwindow.h \
    paintarea.h \
    Graphics/graphics.h \
    Globals.h \
    Graphics/shape.h \
    Graphics/line.h \
    Graphics/polygon.h \
    Graphics/colors.h \
    Graphics/octree.h \
    Graphics/colorquantizer.h

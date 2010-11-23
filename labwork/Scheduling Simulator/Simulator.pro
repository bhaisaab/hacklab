# -------------------------------------------------
# Project created by QtCreator 2010-02-12T17:14:27
# -------------------------------------------------
#QT += network \
#    svg

TARGET = Simulator
TEMPLATE = app
SOURCES += main.cpp \
    visualiser.cpp \
    simulator.cpp \
    gnattwidget.cpp
HEADERS += visualiser.h \
    simulator.h \
    gnattwidget.h

# FORMS += visualiser.ui
OBJECTS_DIR = build
MOC_DIR = build
DESTDIR = .
DEPENDPATH += .
INCLUDEPATH += .

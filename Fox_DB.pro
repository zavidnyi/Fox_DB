TEMPLATE = app
TARGET = fox_db

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    mainscreen.cpp \
    notes.cpp

HEADERS += \
    mainscreen.h \
    notes.h

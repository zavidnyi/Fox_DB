TEMPLATE = app
TARGET = fox_db

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    notes.cpp

HEADERS += \
    notes.h

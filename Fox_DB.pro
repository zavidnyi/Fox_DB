TEMPLATE = app
TARGET = fox_db

QT = core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    databasehandler.cpp \
    editnotecomponent.cpp \
    main.cpp \
    mainscreen.cpp \
    notes.cpp

HEADERS += \
    databasehandler.h \
    editnotecomponent.h \
    mainscreen.h \
    notes.h

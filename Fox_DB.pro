TEMPLATE = app
TARGET = fox_db

QT = core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    cookbook.cpp \
    databasehandler.cpp \
    editnotecomponent.cpp \
    main.cpp \
    mainscreen.cpp \
    notes.cpp \
    recipeeditcomponent.cpp \
    workoutcreationcomponent.cpp \
    workoutplanslist.cpp \
    workoutplanview.cpp

HEADERS += \
    cookbook.h \
    databasehandler.h \
    editnotecomponent.h \
    mainscreen.h \
    notes.h \
    recipeeditcomponent.h \
    workoutcreationcomponent.h \
    workoutplanslist.h \
    workoutplanview.h

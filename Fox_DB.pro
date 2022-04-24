TEMPLATE = app
TARGET = fox_db

QT = core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    databasehandler.cpp \
    editnotecomponent.cpp \
    main.cpp \
    mainscreen.cpp \
    notes.cpp \
    workoutcreationcomponent.cpp \
    workoutplanslist.cpp \
    workoutplanview.cpp

HEADERS += \
    databasehandler.h \
    editnotecomponent.h \
    mainscreen.h \
    notes.h \
    workoutcreationcomponent.h \
    workoutplanslist.h \
    workoutplanview.h

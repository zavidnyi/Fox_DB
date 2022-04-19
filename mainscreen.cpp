#include "mainscreen.h"
#include "notes.h"

mainscreen::mainscreen(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(700, 500);
    name = new QLabel("🦊", this);
    name->setFont(QFont("lucida", 108));
    name->setFixedWidth(700);
    name->setFixedHeight(150);
    name->setAlignment(Qt::AlignCenter);

    notes = new QPushButton("Notes App", this);
    workouts = new QPushButton("Workouts App", this);
    cookbook = new QPushButton("Cookbook App", this);
    reminders = new QPushButton("Reminders App", this);

    hstack = new QHBoxLayout(this);
    hstack->addWidget(notes);
    hstack->addWidget(workouts);
    hstack->addWidget(cookbook);
    hstack->addWidget(reminders);
    connect(notes, SIGNAL (clicked(bool)), this, SLOT (openNotes()));
}

void mainscreen::openNotes() {
    hide();
    Notes *note = new Notes();
    note->show();
}

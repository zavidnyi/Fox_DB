#include "mainscreen.h"
#include "notes.h"
#include "workoutplanslist.h"

mainscreen::mainscreen(QWidget *parent, DatabaseHandler *_dbHandler)
    : QWidget{parent}
{
    dbHandler = _dbHandler;
    setFixedSize(700, 500);
    name = new QLabel("🦊", this);
    name->setFont(QFont("lucida", 108));
    name->setFixedWidth(700);
    name->setFixedHeight(150);
    name->setAlignment(Qt::AlignCenter);

    notes = new QPushButton("Notes App", this);
    connect(notes, SIGNAL (clicked(bool)), this, SLOT (openNotes()));

    workouts = new QPushButton("Workouts App", this);
    connect(workouts, SIGNAL (clicked(bool)), this, SLOT (openWorkoutPlans()));

    cookbook = new QPushButton("Cookbook App", this);

    hstack = new QHBoxLayout(this);
    hstack->addWidget(notes);
    hstack->addWidget(workouts);
    hstack->addWidget(cookbook);
}

void mainscreen::openNotes() {
    hide();
    Notes *note = new Notes(nullptr, dbHandler);
    note->show();
    connect(note, SIGNAL (notesClosed()), this, SLOT (show()));
}

void mainscreen::openWorkoutPlans()
{
    hide();
    WorkoutPlansList *workoutPlans = new WorkoutPlansList(nullptr, dbHandler);
    workoutPlans->show();
    connect(workoutPlans, SIGNAL (workoutPlansClosed()), this, SLOT (show()));
}

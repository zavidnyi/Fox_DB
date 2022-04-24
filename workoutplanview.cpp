#include "workoutplanview.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QGroupBox>
#include "workoutcreationcomponent.h"

WorkoutPlanView::WorkoutPlanView(QWidget *parent, DatabaseHandler *_dbHandler, const QString &curId)
    : QWidget{parent}
{
    setAttribute( Qt::WA_DeleteOnClose, true ); // Widget will be deleted automatically when closed
    id = curId;
    dbHandler = _dbHandler;
    connect(dbHandler, SIGNAL (downloadDone()), this, SLOT (updateData()));
    setFixedSize(700, 500);

    QPushButton *backBtn = new QPushButton("Back", this);
    connect(backBtn, &QPushButton::clicked, this, &WorkoutPlanView::saveAndClose);


    header = new QLabel("Edit workout plan", this);
    header->setFont(QFont("lucida", 24, QFont::Bold, false));
    header->setAlignment(Qt::AlignCenter);

    title = new QPlainTextEdit(this);
    if (id.length() > 0) {
        title->setPlainText(dbHandler->workoutPlans.object()[id].toObject()["Title"].toObject()["text"].toString());
    }
    QFontMetrics m (title -> font());
    int RowHeight = m.lineSpacing();
    title->setFixedHeight(1* RowHeight + 8); // Title text field height is set to one line, 8 is margin

    addWorkout = new QPushButton("add new workout", this);
    connect(addWorkout, &QPushButton::clicked, this, [this]{openWorkoutCreation();});

    // widget overhead is neccessary to make it scrollable
    QWidget *widget = new QWidget(this);
    workoutsScroll = new QScrollArea(this);
    workoutsScroll->setWidgetResizable( true );
    workouts = new QVBoxLayout(widget);
    widget->setLayout(workouts);
    workoutsScroll->setWidget(widget);

    vstack = new QVBoxLayout(this);
    vstack->addWidget(header);
    vstack->addWidget(title);
    vstack->addWidget(addWorkout);
    vstack->addWidget(workoutsScroll);
    updateData();
}

void WorkoutPlanView::updateData()
{
    qDebug() << "updating";
    // delete old notes views
    QLayoutItem *child;
    while ((child = workouts->takeAt(0)) != 0) {
      delete child->widget();
      delete child->layout();
    }

    QJsonObject json = dbHandler->workoutPlans.object()[id].toObject()["workouts"].toObject();
    for (const QString &key: json.keys()) {
        QJsonObject obj = json.value(key).toObject();

        // delete button deletes note from DB
        QPushButton *deleteBtn = new QPushButton("Delete", this);
        connect(deleteBtn, &QPushButton::clicked, dbHandler, [this,key]{
            dbHandler->deleteEntry("workoutPlans" , id+"/workouts/" + key);
        });

        QHBoxLayout *buttons = new QHBoxLayout;
        buttons->addWidget(deleteBtn);

        QVBoxLayout *vbox = new QVBoxLayout;
        vbox->setSizeConstraint(QLayout::SetMinimumSize);

        vbox->addWidget(new QLabel(obj["Title"].toString(), this));

        for (const auto &element: obj["Exercises"].toArray()) {
            QJsonObject exerciseData = element.toObject();
            QHBoxLayout *exercise = new QHBoxLayout;
            exercise->addWidget(new QLabel("Name: " + exerciseData["Name"].toString(), this));
            exercise->addWidget(new QLabel("Sets: " + QString::number(exerciseData["Sets"].toInt()), this));
            exercise->addWidget(new QLabel("Reps: " + QString::number(exerciseData["Reps"].toInt()), this));
            vbox->addLayout(exercise);
        }

        vbox->addLayout(buttons);

        QGroupBox *gBox = new QGroupBox(this);
        gBox->setLayout(vbox);
        gBox->setMinimumSize(600, 150);

        workouts->addWidget(gBox, 0, Qt::AlignTop);
    }

}

void WorkoutPlanView::openWorkoutCreation(const QString &workoutId)
{
    WorkoutCreationComponent *wcc = new WorkoutCreationComponent(nullptr, dbHandler, id, workoutId);
    hide();
    wcc->show();
    connect(wcc, &WorkoutCreationComponent::workoutCreatedAndClosed, this, [this]{updateData(); show();});

}

void WorkoutPlanView::saveAndClose()
{
    QVariantMap workoutPlan;
    QVariantMap titleText;
    titleText["text"] = title->toPlainText();
    workoutPlan["Title"] = titleText;

    QString location("workoutPlans");

    // if given id update note, otw. create new note
    if (id.length() > 0)
        dbHandler->updateEntry(QJsonDocument::fromVariant(titleText), location, id + "/Title");
    else
        dbHandler->uploadToDatabase(QJsonDocument::fromVariant(workoutPlan), location);
    emit workoutPlanClosed();
    close();
}

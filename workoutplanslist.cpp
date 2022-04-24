#include "workoutplanslist.h"
#include <QJsonObject>
#include <QGroupBox>
#include "workoutplanview.h"

WorkoutPlansList::WorkoutPlansList(QWidget *parent, DatabaseHandler *_dbHandler)
    : QWidget{parent}
{
    setAttribute( Qt::WA_DeleteOnClose, true ); // Widget will be deleted automatically when closed

    dbHandler = _dbHandler;
    setFixedWidth(700);
    setMinimumHeight(500);

    QPushButton *backBtn = new QPushButton("Back", this);
    connect(backBtn, &QPushButton::clicked, this, [this]{
        emit workoutPlansClosed();
        close();
    });

    header = new QLabel("My Workout Plans", this);
    header->setFont(QFont("lucida", 24, QFont::Bold, false));
    header->setAlignment(Qt::AlignCenter);

    addWorkoutPlan = new QPushButton("add new", this);
    connect(addWorkoutPlan, SIGNAL (clicked(bool)), this, SLOT (openWorkoutPlan()));

    // widget overhead is neccessary to make it scrollable
    QWidget *widget = new QWidget(this);
    workoutPlansScroll = new QScrollArea(this);
    workoutPlansScroll->setWidgetResizable( true );
    workoutPlans = new QVBoxLayout(widget);
    widget->setLayout(workoutPlans);
    workoutPlansScroll->setWidget(widget);

    vstack = new QVBoxLayout(this);
    vstack->addWidget(header);
    vstack->addWidget(addWorkoutPlan);
    vstack->addWidget(workoutPlansScroll);

    // every time we get new data from DB update view
    dbHandler->downloadFromDatabase(QString("workoutPlans"));
    connect(dbHandler, SIGNAL (downloadDone()), this, SLOT (updateData()));
}

void WorkoutPlansList::updateData()
{
    // delete old notes views
    QLayoutItem *child;
    while ((child = workoutPlans->takeAt(0)) != 0) {
      delete child->widget();
    }


    QJsonObject json = dbHandler->workoutPlans.object();
    for (const QString &key: json.keys()) {
        QJsonObject obj = json.value(key).toObject();
//        qDebug() << obj;
        QString title = obj["Title"].toObject()["text"].toString();

        QPushButton *openBtn = new QPushButton("Open", this);
        connect(openBtn, &QPushButton::clicked, this, [this, key]{openWorkoutPlan(key);});

        // delete button deletes wokroutPlan from DB
        QPushButton *deleteBtn = new QPushButton("Delete", this);
        connect(deleteBtn, &QPushButton::clicked, dbHandler, [this,key]{dbHandler->deleteEntry("workoutPlans", key);});

        QHBoxLayout *buttons = new QHBoxLayout;
        buttons->addWidget(openBtn);
        buttons->addWidget(deleteBtn);

        QVBoxLayout *vbox = new QVBoxLayout(this);
        vbox->addLayout(buttons);

        QGroupBox *gBox = new QGroupBox(title,this);
        gBox->setLayout(vbox);
        gBox->setMinimumSize(600, 150);

        workoutPlans->addWidget(gBox, 0, Qt::AlignTop);
    }
}

void WorkoutPlansList::openWorkoutPlan(const QString &id)
{
    hide();
    WorkoutPlanView *workoutPlan = new WorkoutPlanView(nullptr, dbHandler,id);
    workoutPlan->show();
    connect(workoutPlan,  SIGNAL(workoutPlanClosed()), this, SLOT (show()));
    connect(workoutPlan,  SIGNAL(workoutPlanClosed()), this, SLOT (updateData()));

}

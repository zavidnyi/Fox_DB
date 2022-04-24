#include "workoutcreationcomponent.h"
#include <QInputDialog>
#include <QGroupBox>

WorkoutCreationComponent::WorkoutCreationComponent(
            QWidget *parent,
            DatabaseHandler *_dbHandler,
            const QString &parentId,
            const QString &curId
        )
    : QWidget{parent}
{
    setAttribute( Qt::WA_DeleteOnClose, true ); // Widget will be deleted automatically when closed
    id = curId;
    planId = parentId;
    dbHandler = _dbHandler;
    setFixedSize(700, 500);

    QPushButton *saveBtn = new QPushButton("Create Workout", this);
    connect(saveBtn, &QPushButton::clicked, this, [this]{
        QVariantMap data;
        data["Title"] = title->toPlainText();
        data["Exercises"] = exercisesMap;
        dbHandler->uploadToDatabase(QJsonDocument::fromVariant(data), "workoutPlans", planId + "/workouts");
        emit workoutCreatedAndClosed();
        close();
    });

    header = new QLabel("Workout Creation", this);
    header->setFont(QFont("lucida", 24, QFont::Bold, false));
    header->setAlignment(Qt::AlignCenter);

    title = new QPlainTextEdit(this);
    QFontMetrics m (title -> font());
    int RowHeight = m.lineSpacing();
    title->setFixedHeight(1* RowHeight + 8); // Title text field height is set to one line, 8 is margin

    addExercise = new QPushButton("add exercise", this);
    connect(addExercise, SIGNAL (clicked(bool)), this, SLOT (exerciseCreationDialog()));

    // widget overhead is neccessary to make it scrollable
    QWidget *widget = new QWidget(this);
    exercisesScroll = new QScrollArea(this);
    exercisesScroll ->setWidgetResizable( true );
    exercises = new QVBoxLayout(widget);
    widget->setLayout(exercises);
    exercisesScroll ->setWidget(widget);

    vstack = new QVBoxLayout(this);
    vstack->addWidget(header);
    vstack->addWidget(title);
    vstack->addWidget(addExercise);
    vstack->addWidget(exercisesScroll);
    vstack->addWidget(saveBtn);

}

void WorkoutCreationComponent::updateData()
{
    // delete old notes views
    QLayoutItem *child;
    while ((child = exercises->takeAt(0)) != 0) {
      delete child->widget();
    }

    for(QVariantMap::const_iterator iter = exercisesMap.cbegin(); iter != exercisesMap.cend(); ++iter) {
        QMap map = iter.value().toMap();
        qDebug() << iter.key() << " " << iter.value().toMap();
        QPushButton *deleteBtn = new QPushButton("Delete", this);
        connect(deleteBtn, &QPushButton::clicked, this, [this,iter]{
            exercisesMap.erase(iter);
            updateData();
        });

        QHBoxLayout *info = new QHBoxLayout;
        info->addWidget(new QLabel("Name: " + map["Name"].toString(),this));
        info->addWidget(new QLabel("Sets: " + map["Sets"].toString(),this));
        info->addWidget(new QLabel("Reps: " + map["Reps"].toString(),this));

        QHBoxLayout *buttons = new QHBoxLayout;
        buttons->addWidget(deleteBtn);

        QVBoxLayout *vbox = new QVBoxLayout;
        vbox->setSizeConstraint(QLayout::SetMinimumSize);

        vbox->addLayout(info);
        vbox->addLayout(buttons);

        QGroupBox *gBox = new QGroupBox(this);
        gBox->setLayout(vbox);
        gBox->setMinimumSize(600, 150);

        exercises->addWidget(gBox, 0, Qt::AlignTop);
    }
}

void WorkoutCreationComponent::exerciseCreationDialog()
{
   bool ok;
   QString name = QInputDialog::getText(this, tr("Adding Exercise"),
                                        tr("Exercise Name:"), QLineEdit::Normal,
                                        "", &ok);
   if (!ok || name.isEmpty()) return;

   int sets = QInputDialog::getInt(this, tr("Adding Exercise"),
                                    tr("Number of sets:"), 0, 1, 100, 1, &ok);
   if (!ok || sets < 1) return;

   int reps = QInputDialog::getInt(this, tr("Adding Exercise"),
                                    tr("Number of repetitions:"), 0, 1, 100, 1, &ok);
   if (!ok || reps < 1) return;

   QVariantMap exercise;
   exercise["Name"] = name;
   exercise["Sets"] = sets;
   exercise["Reps"] = reps;
   exercisesMap[QString::number(exercisesMap.size())] = exercise;
   updateData();
}

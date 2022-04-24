#ifndef WORKOUTPLANVIEW_H
#define WORKOUTPLANVIEW_H

#include <QWidget>
#include "databasehandler.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QPlainTextEdit>


class WorkoutPlanView : public QWidget
{
    Q_OBJECT
public:
    explicit WorkoutPlanView(QWidget *parent = nullptr, DatabaseHandler *_dbHandler = nullptr, const QString &curId = "");
private:
    QString id;
    DatabaseHandler *dbHandler;
    QLabel *header;
    QVBoxLayout *vstack;
    QPlainTextEdit *title;
    QPushButton *addWorkout;
    QScrollArea *workoutsScroll;
    QVBoxLayout *workouts;
private slots:
    void updateData();
    void openWorkoutCreation(const QString &id = "");
    void saveAndClose();
signals:
    void workoutPlanClosed();

};

#endif // WORKOUTPLANVIEW_H

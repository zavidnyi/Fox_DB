#ifndef WORKOUTPLANSLIST_H
#define WORKOUTPLANSLIST_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include "databasehandler.h"

class WorkoutPlansList : public QWidget
{
    Q_OBJECT
public:
    explicit WorkoutPlansList(QWidget *parent = nullptr, DatabaseHandler *_dbHandler = nullptr);
private:
    QLabel *header;
    QVBoxLayout *vstack;
    DatabaseHandler *dbHandler;
    QPushButton *addWorkoutPlan;
    QScrollArea *workoutPlansScroll;
    QVBoxLayout *workoutPlans;
private slots:
    void updateData();
    void openWorkoutPlan(const QString &id = "");
signals:
    void workoutPlansClosed();
};

#endif // WORKOUTPLANSLIST_H

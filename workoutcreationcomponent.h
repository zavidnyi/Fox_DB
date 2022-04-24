#ifndef WORKOUTCREATIONCOMPONENT_H
#define WORKOUTCREATIONCOMPONENT_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QScrollArea>
#include "databasehandler.h"

class WorkoutCreationComponent : public QWidget
{
    Q_OBJECT
public:
    explicit WorkoutCreationComponent(
                QWidget *parent = nullptr,
                DatabaseHandler *_dbHandler = nullptr,
                const QString &parentId = "",
                const QString &curId = ""
            );
private:
    QLabel *header;
    QVBoxLayout *vstack;
    QPlainTextEdit *title;
    DatabaseHandler *dbHandler;
    QPushButton *addExercise;
    QScrollArea *exercisesScroll;
    QVBoxLayout *exercises;
    QVariantMap exercisesMap;
    QString id;
    QString planId;
private slots:
    void updateData();
    void exerciseCreationDialog();
signals:
    void workoutCreatedAndClosed();
};

#endif // WORKOUTCREATIONCOMPONENT_H

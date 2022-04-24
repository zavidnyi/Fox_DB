#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "databasehandler.h"

class mainscreen : public QWidget
{
    Q_OBJECT
public:
    explicit mainscreen(QWidget *parent = nullptr, DatabaseHandler *_dbHandler = nullptr);
private:

    QLabel *name;
    QVBoxLayout *vstack;
    QHBoxLayout *hstack;
    QPushButton *notes;
    QPushButton *workouts;
    QPushButton *cookbook;
    DatabaseHandler *dbHandler;
private slots:
    void openNotes();
    void openWorkoutPlans();
signals:

};

#endif // MAINSCREEN_H

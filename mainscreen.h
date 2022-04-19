#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class mainscreen : public QWidget
{
    Q_OBJECT
public:
    explicit mainscreen(QWidget *parent = nullptr);
private:

    QLabel *name;
    QVBoxLayout *vstack;
    QHBoxLayout *hstack;
    QPushButton *notes;
    QPushButton *workouts;
    QPushButton *cookbook;
    QPushButton *reminders;
private slots:
    void openNotes();
signals:

};

#endif // MAINSCREEN_H

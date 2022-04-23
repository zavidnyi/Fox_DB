#ifndef NOTES_H
#define NOTES_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include "databasehandler.h"

class Notes : public QWidget
{
    Q_OBJECT
public:
    explicit Notes(QWidget *parent = nullptr, DatabaseHandler *_dbHandler = nullptr);
private:
    QLabel *header;
    QVBoxLayout *vstack;
    DatabaseHandler *dbHandler;
    QPushButton *addNote;
private slots:
    void updateData();
    void openEditNote();
};

#endif // NOTES_H

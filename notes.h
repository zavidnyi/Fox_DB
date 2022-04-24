#ifndef NOTES_H
#define NOTES_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
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
    QScrollArea *notesScroll;
    QVBoxLayout *notes;
private slots:
    void updateData();
    void openEditNote(const QString &id = "", const QString &title = "", const QString &text = "");
signals:
     void notesClosed();
};

#endif // NOTES_H

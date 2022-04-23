#ifndef EDITNOTECOMPONENT_H
#define EDITNOTECOMPONENT_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include "databasehandler.h"

class EditNoteComponent : public QWidget
{
    Q_OBJECT
public:
    explicit EditNoteComponent(QWidget *parent = nullptr, DatabaseHandler *_dbHandler = nullptr);
private:
    QLabel *header;
    QPlainTextEdit *title;
    QPlainTextEdit *text;
    QPushButton *saveButton;
    QVBoxLayout *vstack;
    DatabaseHandler *dbHandler;

private slots:
     void saveNote();
signals:
     void editClosed();
};

#endif // EDITNOTECOMPONENT_H

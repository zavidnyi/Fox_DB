#include "notes.h"
#include <QJsonObject>
#include <QGroupBox>
#include <QVBoxLayout>
#include "editnotecomponent.h"

Notes::Notes(QWidget *parent, DatabaseHandler *_dbHandler)
    : QWidget{parent}
{
    setAttribute( Qt::WA_DeleteOnClose, true ); // Widget will be deleted automatically when closed

    dbHandler = _dbHandler;
    setFixedWidth(700);
    setMinimumHeight(500);

    header = new QLabel("My notes", this);
    header->setFont(QFont("lucida", 24, QFont::Bold, false));
    header->setAlignment(Qt::AlignCenter);

    addNote = new QPushButton("add new", this);
    connect(addNote, SIGNAL (clicked(bool)), this, SLOT (openEditNote()));

    vstack = new QVBoxLayout(this);
    vstack->addWidget(header, 0, Qt::AlignTop);
    vstack->addWidget(addNote, 0, Qt::AlignTop);
    QString location("notes");
    dbHandler->downloadFromDatabase(&location);
    connect(dbHandler, SIGNAL (downloadDone()), this, SLOT (updateData()));
}

void Notes::updateData()
{
    QJsonObject json = dbHandler->notes.object();
    foreach(const QJsonValue &value, json) {
        QJsonObject obj = value.toObject();
        QGroupBox *gBox = new QGroupBox(obj["Title"].toString(),this);
        QVBoxLayout *vbox = new QVBoxLayout;
        vbox->addWidget(new QLabel(obj["Text"].toString(), this));
        gBox->setLayout(vbox);
        gBox->setFixedHeight(100);
        vstack->addWidget(gBox, 0, Qt::AlignTop);
    }
}

void Notes::openEditNote()
{
    hide();
    EditNoteComponent *edit = new EditNoteComponent(nullptr, dbHandler);
    connect(edit, SIGNAL (editClosed()), this, SLOT (show()));
    edit->show();
}


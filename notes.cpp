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

    // widget overhead is neccessary to make it scrollable
    QWidget *widget = new QWidget(this);
    notesScroll = new QScrollArea(this);
    notesScroll->setWidgetResizable( true );
    notes = new QVBoxLayout(widget);
    widget->setLayout(notes);
    notesScroll->setWidget(widget);

    vstack = new QVBoxLayout(this);
    vstack->addWidget(header);
    vstack->addWidget(addNote);
    vstack->addWidget(notesScroll);
    QString location("notes");
    dbHandler->downloadFromDatabase(&location);
    connect(dbHandler, SIGNAL (downloadDone()), this, SLOT (updateData()));
}

void Notes::updateData()
{
    QJsonObject json = dbHandler->notes.object();
    QLayoutItem *child;
    while ((child = notes->takeAt(0)) != 0) {
      delete child;
    }
    for (const QString &key: json.keys()) {
        QJsonObject obj = json.value(key).toObject();
        qDebug() << obj;
        QString title = obj["Title"].toString();
        QString text = obj["Text"].toString();
        QGroupBox *gBox = new QGroupBox(title,this);
        QVBoxLayout *vbox = new QVBoxLayout;
        vbox->addWidget(new QLabel(text, this));
        QPushButton *editBtn = new QPushButton("Edit", this);
        connect(editBtn, &QPushButton::clicked, this, [this, key, title, text]{openEditNote(key, title, text);});
        vbox->addWidget(editBtn);
        gBox->setLayout(vbox);
        gBox->setMinimumSize(600, 80);
        notes->addWidget(gBox, 0, Qt::AlignTop);
    }
}

void Notes::openEditNote(const QString &id, const QString &title, const QString &text)
{
    qDebug() << id;
    hide();
    EditNoteComponent *edit = new EditNoteComponent(nullptr, dbHandler, id, title, text);
    connect(edit, SIGNAL (editClosed()), this, SLOT (show()));
    edit->show();
}


#include "notes.h"
#include <QJsonObject>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "editnotecomponent.h"

Notes::Notes(QWidget *parent, DatabaseHandler *_dbHandler)
    : QWidget{parent}
{
    setAttribute( Qt::WA_DeleteOnClose, true ); // Widget will be deleted automatically when closed

    dbHandler = _dbHandler;
    setFixedWidth(700);
    setMinimumHeight(500);

    QPushButton *backBtn = new QPushButton("Back", this);
    connect(backBtn, &QPushButton::clicked, this, [this]{
        emit notesClosed();
        close();
    });

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

    // every time we get new data from DB update view
    dbHandler->downloadFromDatabase(QString("notes"));
    connect(dbHandler, SIGNAL (downloadDone()), this, SLOT (updateData()));
}

void Notes::updateData()
{   
    // delete old notes views
    QLayoutItem *child;
    while ((child = notes->takeAt(0)) != 0) {
      delete child->widget();
    }


    QJsonObject json = dbHandler->notes.object();
    for (const QString &key: json.keys()) {
        QJsonObject obj = json.value(key).toObject();
//        qDebug() << obj;
        QString title = obj["Title"].toString();
        QString text = obj["Text"].toString();

        // edit button opens edit note component
        QPushButton *editBtn = new QPushButton("Edit", this);
        connect(editBtn, &QPushButton::clicked, this, [this, key, title, text]{openEditNote(key, title, text);});

        // delete button deletes note from DB
        QPushButton *deleteBtn = new QPushButton("Delete", this);
        connect(deleteBtn, &QPushButton::clicked, dbHandler, [this,key]{dbHandler->deleteEntry("notes", key);});

        QHBoxLayout *buttons = new QHBoxLayout;
        buttons->addWidget(editBtn);
        buttons->addWidget(deleteBtn);

        QVBoxLayout *vbox = new QVBoxLayout;
        vbox->setSizeConstraint(QLayout::SetMinimumSize);
        QLabel *textLabel = new QLabel(text, this);
        textLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        textLabel->setWordWrap(true);
        vbox->addWidget(textLabel);
        vbox->addLayout(buttons);

        QGroupBox *gBox = new QGroupBox(title,this);
        gBox->setLayout(vbox);
        gBox->setMinimumSize(600, 150);

        notes->addWidget(gBox, 0, Qt::AlignTop);
    }
}

void Notes::openEditNote(const QString &id, const QString &title, const QString &text)
{
//    qDebug() << id;
    hide();
    EditNoteComponent *edit = new EditNoteComponent(nullptr, dbHandler, id, title, text);
    connect(edit, SIGNAL (editClosed()), this, SLOT (show()));
    edit->show();
}


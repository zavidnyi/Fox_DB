#include "editnotecomponent.h"

#include <QFontMetrics>
#include <QVariantMap>
#include <QJsonDocument>

EditNoteComponent::EditNoteComponent(
            QWidget *parent,
            DatabaseHandler *_dbHandler,
            const QString &curId,
            const QString &curTitle,
            const QString &curText
        )
    : QWidget{parent}
{
    setAttribute( Qt::WA_DeleteOnClose, true ); // Widget will be deleted automatically when closed

    id = curId;
    dbHandler = _dbHandler;
    setFixedSize(700, 500);

    header = new QLabel("Edit note", this);
    header->setFont(QFont("lucida", 24, QFont::Bold, false));
    header->setAlignment(Qt::AlignCenter);

    title = new QPlainTextEdit(this);
    title->setPlainText(curTitle);
    QFontMetrics m (title -> font());
    int RowHeight = m.lineSpacing();
    title->setFixedHeight(1* RowHeight + 8); // Title text field height is set to one line, 8 is margin

    text = new QPlainTextEdit(this);
    text->setPlainText(curText);

    // on button click save note
    saveButton = new QPushButton("Save", this);
    connect(saveButton, SIGNAL (clicked(bool)), this, SLOT (saveNote()));

    vstack = new QVBoxLayout(this);
    vstack->addWidget(header);
    vstack->addWidget(new QLabel("Title:", this));
    vstack->addWidget(title);
    vstack->addWidget(new QLabel("Text:", this));
    vstack->addWidget(text);
    vstack->addWidget(saveButton);
}

void EditNoteComponent::saveNote() {
    QVariantMap note;
    note["Title"] = title->toPlainText();
    note["Text"] = text->toPlainText();

    QJsonDocument jsonDoc = QJsonDocument::fromVariant(note);
    QString location("notes");

    // if given id update note, otw. create new note
    if (id.length() > 0)
        dbHandler->updateEntry(jsonDoc, location, id);
    else
        dbHandler->uploadToDatabase(jsonDoc, location);

    emit editClosed();
    close();
}

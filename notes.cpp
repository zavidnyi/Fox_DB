#include "notes.h"
#include <QFontMetrics>

Notes::Notes(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(500, 500);

    header = new QLabel("Edit note", this);
    header->setFont(QFont("lucida", 24, QFont::Bold, false));
    header->setAlignment(Qt::AlignCenter);

    title = new QPlainTextEdit(this);
    title->setDocumentTitle("Title");
    QFontMetrics m (title -> font());
    int RowHeight = m.lineSpacing();
    title->setFixedHeight(1* RowHeight + 8);

    text = new QPlainTextEdit(this);

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

void Notes::saveNote() {
    saveButton->setText(title->toPlainText());
}

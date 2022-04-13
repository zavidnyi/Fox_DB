#include "notes.h"

Notes::Notes(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(500, 500);
    vstack = new QVBoxLayout(this);
    text = new QTextEdit(this);
    header = new QLabel("Notes Application", this);
    header->setFont(QFont("lucida", 24, QFont::Bold, false));
    vstack->addWidget(header);
    vstack->addWidget(text);
//    header->setAlignment(Qt::AlignCenter);
//    text->setGeometry(20, 20, 200, 200);
}

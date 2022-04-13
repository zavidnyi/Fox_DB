#ifndef NOTES_H
#define NOTES_H

#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QVBoxLayout>

class Notes : public QWidget
{
    Q_OBJECT
public:
    explicit Notes(QWidget *parent = nullptr);
private:
    QLabel *header;
    QTextEdit *text;
    QVBoxLayout *vstack;
signals:

};

#endif // NOTES_H

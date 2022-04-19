#ifndef NOTES_H
#define NOTES_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class Notes : public QWidget
{
    Q_OBJECT
public:
    explicit Notes(QWidget *parent = nullptr);
private:
    QLabel *header;
    QPlainTextEdit *title;
    QPlainTextEdit *text;
    QPushButton *saveButton;
    QVBoxLayout *vstack;

private slots:
     void saveNote();
};

#endif // NOTES_H

#include <QApplication>
#include "notes.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    Notes *note = new Notes();

    note->show();
    return app.exec();
    }

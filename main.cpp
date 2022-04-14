#include <QApplication>
#include "mainscreen.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    mainscreen *ms = new mainscreen();

    ms->show();
    return app.exec();
    }

#include <QApplication>
#include "mainscreen.h"
#include "databasehandler.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

//    mainscreen *ms = new mainscreen();

    DatabaseHandler dbHandler;

//    ms->show();
    return app.exec();
    }

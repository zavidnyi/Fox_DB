#include <QApplication>
#include "mainscreen.h"
#include "databasehandler.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    DatabaseHandler dbHandler;
    mainscreen *ms = new mainscreen(nullptr, &dbHandler);

    ms->show();
    return app.exec();
    }

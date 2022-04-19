#include "databasehandler.h"
#include <QJsonDocument>
#include <QVariantMap>

DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject{parent}
{
    networkManager = new QNetworkAccessManager( this );
    networkReply = networkManager->get(QNetworkRequest( QUrl("https://fox-db-4b8b8-default-rtdb.europe-west1.firebasedatabase.app/Notes.json")));
    connect(networkReply, SIGNAL(readyRead()), this, SLOT (networkReplyReadyToRead()));
}

void DatabaseHandler::networkReplyReadyToRead()
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(networkReply->readAll());
    qDebug() << jsonDoc["qwelashj22"]["Title"].toString();
}

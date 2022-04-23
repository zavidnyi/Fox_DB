#include "databasehandler.h"
#include <QJsonDocument>
#include <QVariantMap>
#include <QJsonObject>

DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject{parent}
{
    networkManager = new QNetworkAccessManager( this );
//    QNetworkRequest newRequest( QUrl("https://foxdb-2b7f2-default-rtdb.europe-west1.firebasedatabase.app/notes.json"));
//    networkReply = networkManager->get(newRequest);
//    connect(networkReply, SIGNAL(readyRead()), this, SLOT (networkReplyReadyToRead()));
}

void DatabaseHandler::uploadToDatabase(const QJsonDocument &jsonDoc, QString *location)
{
    QNetworkRequest newRequest( QUrl("https://foxdb-2b7f2-default-rtdb.europe-west1.firebasedatabase.app/notes.json"));
    newRequest.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    try {
        networkReply = networkManager->post(newRequest, jsonDoc.toJson());

    } catch (const std::exception& e) // reference to the base of a polymorphic object
    {
        qDebug() << e.what(); // information from length_error printed
    }
    connect(networkReply, SIGNAL(readyRead()), this, SLOT (networkReplyReadyToRead()));
}

void DatabaseHandler::downloadFromDatabase(QString *location)
{
    QNetworkRequest newRequest( QUrl("https://foxdb-2b7f2-default-rtdb.europe-west1.firebasedatabase.app/notes.json"));
    networkReply = networkManager->get(newRequest);
    downloadLocation = location;
    connect(networkReply, SIGNAL(readyRead()), this, SLOT (setData()));
}
void DatabaseHandler::networkReplyReadyToRead()
{
    qDebug() << networkReply->readAll();
    emit downloadDone();
}

void DatabaseHandler::setData()
{
    qDebug() << downloadLocation;
    notes = QJsonDocument::fromJson(networkReply->readAll());
    emit downloadDone();
}

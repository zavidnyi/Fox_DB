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

void DatabaseHandler::uploadToDatabase(const QJsonDocument &jsonDoc, const QString &location, const QString &id)
{
    QString url(dbUrl);
    url.append(location);
    if (id.length() > 0) {
        url.append("/");
        url.append(id);
    }
    url.append(".json");
    QNetworkRequest newRequest = QNetworkRequest( QUrl(url));
    newRequest.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    try {
        networkReply = networkManager->post(newRequest, jsonDoc.toJson());

    } catch (const std::exception& e) // reference to the base of a polymorphic object
    {
        qDebug() << e.what(); // information from length_error printed
    }
    connect(networkReply, &QNetworkReply::readyRead, this, [this, location]{uploadDone(location);});
}

void DatabaseHandler::downloadFromDatabase(const QString &location)
{
    QString url(dbUrl);
    url.append(location);
    url.append(".json");

    QNetworkRequest newRequest = QNetworkRequest( QUrl(url) );

    networkReply = networkManager->get(newRequest);
    downloadLocation = location;
    connect(networkReply, &QNetworkReply::readyRead, this, [this, location]{setData(location);});
}

void DatabaseHandler::updateEntry(const QJsonDocument &jsonDoc, const QString &location, const QString &id)
{
    QString url(dbUrl);
    url.append(location);
    url.append("/");
    url.append(id);
    url.append(".json");

    QNetworkRequest newRequest = QNetworkRequest( QUrl(url) );
    newRequest.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));

    networkReply = networkManager->put(newRequest, jsonDoc.toJson());
    connect(networkReply, &QNetworkReply::readyRead, this, [this, location]{uploadDone(location);});
}


void DatabaseHandler::uploadDone(const QString &location)
{
    qDebug() << networkReply->readAll();
    downloadFromDatabase(location);
}

void DatabaseHandler::setData(const QString &location)
{
//    qDebug() << downloadLocation;
    QJsonDocument data = QJsonDocument::fromJson(networkReply->readAll());

    if (location == "notes") {
        notes = data;
    } else if (location.contains("workoutPlans")) {
        workoutPlans = data;
    }

    emit downloadDone();
}

void DatabaseHandler::deleteEntry(const QString &location, const QString &id)
{
    QString url(dbUrl);
    url.append(location);
    if (id.length() > 0) {
        url.append("/");
        url.append(id);
    }
    url.append(".json");

    QNetworkRequest newRequest = QNetworkRequest( QUrl(url) );


    networkReply = networkManager->deleteResource(newRequest);
    connect(networkReply, &QNetworkReply::readyRead, this, [this, location]{uploadDone(location);});
}

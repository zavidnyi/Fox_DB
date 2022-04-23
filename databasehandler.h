#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>


class DatabaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseHandler(QObject *parent = nullptr);
    void uploadToDatabase(const QJsonDocument &jsonDoc, QString *location);
    void downloadFromDatabase(QString *location);
    QJsonDocument notes;
private:
    QNetworkAccessManager *networkManager;
    QNetworkReply *networkReply;
    QString *downloadLocation;
signals:
    void downloadDone();
private slots:
    void networkReplyReadyToRead();
    void setData();

};

#endif // DATABASEHANDLER_H

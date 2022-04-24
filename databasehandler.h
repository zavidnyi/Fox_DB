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
    void uploadToDatabase(const QJsonDocument &jsonDoc, const QString &location, const QString &id = "");
    void downloadFromDatabase(const QString &location);
    void updateEntry(const QJsonDocument &jsonDoc, const QString &location, const QString &id);
    QJsonDocument notes;
    QJsonDocument workoutPlans;
private:
    QNetworkAccessManager *networkManager;
    QNetworkReply *networkReply;
    QString downloadLocation;
    const QString dbUrl = QString("https://foxdb-2b7f2-default-rtdb.europe-west1.firebasedatabase.app/");
signals:
    void downloadDone();
private slots:
    void uploadDone(const QString &location);
    void setData(const QString &location);
public slots:
    void deleteEntry(const QString &location, const QString &id = "");

};

#endif // DATABASEHANDLER_H

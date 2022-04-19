#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>


class DatabaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseHandler(QObject *parent = nullptr);
private:
    QNetworkAccessManager *networkManager;
    QNetworkReply *networkReply;
private slots:
    void networkReplyReadyToRead();

};

#endif // DATABASEHANDLER_H

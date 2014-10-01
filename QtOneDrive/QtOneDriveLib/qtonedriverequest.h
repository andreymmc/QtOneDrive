#ifndef QTONEDRIVEREQUEST_H
#define QTONEDRIVEREQUEST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>

class QtOneDriveRequest : public QObject
{
    Q_OBJECT
public:
    explicit QtOneDriveRequest(QObject *parent = 0);

    QNetworkReply *get(const QUrl &url);
    QNetworkReply *post(const QUrl &url, const QByteArray &data);
    QNetworkReply *remove(const QUrl &url);
    QNetworkReply *put(const QUrl &url, QIODevice *data = 0);
signals:


public slots:

private:


private:
    QNetworkAccessManager *networkManager_ = nullptr;

};

#endif // QTONEDRIVEREQUEST_H

#include "qtonedriverequest.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>

QtOneDriveRequest::QtOneDriveRequest(QObject *parent) :
    QObject(parent)
{
    networkManager_ = new QNetworkAccessManager(this);
}

QNetworkReply *QtOneDriveRequest::get(const QUrl &url)
{

}

QNetworkReply *QtOneDriveRequest::post(const QUrl &url, const QByteArray &data)
{
    QNetworkRequest request(url);
    request.setHeader( QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );
    return networkManager_->post(request, data);
}

QNetworkReply *QtOneDriveRequest::remove(const QUrl &url)
{

}

QNetworkReply *QtOneDriveRequest::put(const QUrl &url, QIODevice *data)
{

}

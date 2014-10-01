#ifndef QTONEDRIVE_H
#define QTONEDRIVE_H

#include "qtonedrivelib_global.h"
#include <QObject>
#include <QTcpServer>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QDateTime>
#include <QSettings>

namespace {
    #define ONEDRIVE_DEF_LOCAL_PORT  54432
}

class AuthorizationForm;

class QTONEDRIVELIBSHARED_EXPORT QtOneDrive : public QObject
{
    Q_OBJECT

public:
    enum OneDriveState
    {
        Empty,
        SingIn,
        SingOut,

        GetUserInfo,

        UploadFile,
        DownloadFile,
        DeleteFile,

        CreateFolder,
        DeleteFolder
    };

public:
    explicit QtOneDrive(const QString& clientID,
                        const QString& secret,
                        const QString& redirectUri,
                        const QString& userID = "",  //
                        QObject* parent = 0 );
    ~QtOneDrive();

public:

    void signIn();
    bool isSingIn() const { return isSignIn_; }

    void signOut();
    void getUserInfo();

    void uploadFile(const QString &path);
    void downloadFile(const QString &path);
    void refreshToken();
    void getToken();

    void closeAuthorizationForm();

private slots:
    void slot_getTokenFinished();
    void slot_refreshTokenFinished();
    void slot_tokenError(QNetworkReply::NetworkError);

    void slot_singLoadPageSuccess(const QUrl &url);
    void slot_singLoadPageError(const QUrl &url);
signals:

    void singInError( const QString &error );
    void singOutError( const QString &error );

    void authError( const QString &error );
    void uploadFileError( const QString &error );
    void downloadFileError( const QString &error );
    void getUserInfoError( const QString &error );

    void singInSuccess();
    void singOutSuccess();

    void refreshTokenSuccess();
    void uploadFileSuccess();
    void downloadFileSuccess();
    void getUserInfoSuccess();

    void error( const QString &error );
    void progress(const int &progressPercent );
    void finish();

private:

    QUrl singInUrl() const;
    QUrl singOutUrl() const;
    QUrl getTokenUrl() const;

    QUrlQuery getTokenPost() const;
    QUrlQuery refreshTokenPost() const;

    void saveProperties();
    void loadProperties();

private:
    bool startLocalServer();
    void emitError( const QString &desc );
    bool isBusy() const { return state_ != Empty; }

private:
    QString clientID_;
    QString secret_;
    QString authorizationCode_;
    QString redirectURI_;

    QString accessToken_;
    QString refreshToken_;
    QString authenticationToken_;

    QDateTime tokenTime_;
    QDateTime expiredTokenTime_;

    bool isSignIn_ = false;

    QSettings* properties_;

    OneDriveState state_ = Empty;

    QNetworkAccessManager* networkManager_ = nullptr;

    QNetworkReply* getTokenReply_= nullptr;
    QNetworkReply* refreshTokenReply_= nullptr;

    AuthorizationForm* form_ = nullptr;
};

#endif // QTONEDRIVE_H

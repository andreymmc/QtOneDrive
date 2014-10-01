#include "qtonedrive.h"
#include <QUrlQuery>
#include <QDesktopServices>
#include <QRegExp>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QSettings>
#include <QCoreApplication>
#include <QCryptographicHash>

#include "qtonedriverequest.h"
#include "authorizationform.h"

#ifdef _WIN32
#include "windows.h"
#endif

namespace
{
    const char* errorBusy = "QtOneDrive service is busy now";  
}

QtOneDrive::QtOneDrive( const QString &clientID, const QString &secret, const QString &uri, const QString &userID, QObject *parent) :
    QObject( parent ),
    clientID_(clientID),
    secret_(secret),
    redirectURI_( uri )
{
    networkManager_ = new QNetworkAccessManager(this);

    properties_ = new QSettings( QCoreApplication::organizationName(), QCoreApplication::applicationName(), this );
    QString hash = "QtOneDrive_" + QString( QCryptographicHash::hash( (clientID + "\n" + userID).toUtf8() ,QCryptographicHash::Md5).toHex() );
    properties_->beginGroup( hash );

    loadProperties();
}

QtOneDrive::~QtOneDrive()
{

}

void QtOneDrive::signIn()
{
    Q_ASSERT_X( !isBusy(), Q_FUNC_INFO, errorBusy );
    state_ = SingIn;

    form_ = new AuthorizationForm( 0, singInUrl() );
    form_->setAttribute(Qt::WA_DeleteOnClose);
    connect(form_, SIGNAL(success(QUrl)), this, SLOT(slot_singLoadPageSuccess(QUrl)) );
    connect(form_, SIGNAL(error(QUrl)), this, SLOT(slot_singLoadPageError(QUrl)) );
    form_->show();
}

void QtOneDrive::signOut()
{
    Q_ASSERT_X( !isBusy(), Q_FUNC_INFO, errorBusy);
    state_ = SingOut;
}

void QtOneDrive::getUserInfo()
{
    Q_ASSERT_X( !isBusy(), Q_FUNC_INFO, errorBusy);
    state_ = GetUserInfo;
    refreshToken();
}

void QtOneDrive::refreshToken()
{
    if( QDateTime::currentDateTime() < expiredTokenTime_ )
    {
        slot_refreshTokenFinished();
        return;
    }

    tokenTime_ = QDateTime::currentDateTime();
    QNetworkRequest request( getTokenUrl() );
    request.setHeader( QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );
    refreshTokenReply_ = networkManager_->post(request, refreshTokenPost().query(QUrl::FullyEncoded).toUtf8() );
    connect(refreshTokenReply_, SIGNAL(finished()), this, SLOT(slot_refreshTokenFinished()));
    connect(refreshTokenReply_, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slot_tokenError(QNetworkReply::NetworkError)));
}

void QtOneDrive::getToken()
{
    qDebug() << Q_FUNC_INFO;

    tokenTime_ = QDateTime::currentDateTime();

    QNetworkRequest request( getTokenUrl() );
    request.setHeader( QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );
    getTokenReply_ = networkManager_->post(request, getTokenPost().query(QUrl::FullyEncoded).toUtf8() );
    connect(getTokenReply_, SIGNAL(finished()), this, SLOT(slot_getTokenFinished()));
    connect(getTokenReply_, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slot_tokenError(QNetworkReply::NetworkError)));
}

void QtOneDrive::slot_getTokenFinished()
{
    qDebug() << Q_FUNC_INFO;
    QJsonObject json = QJsonDocument::fromJson(getTokenReply_->readAll()).object();
    qDebug() << json;
    accessToken_ = json["access_token"].toString();
    authenticationToken_ = json["authentication_token"].toString();
    expiredTokenTime_ = tokenTime_.addSecs( json["expires_in"].toInt() - 60 );

    emit singInSuccess();
    state_ = Empty;
}

void QtOneDrive::slot_tokenError(QNetworkReply::NetworkError)
{
    qDebug() << Q_FUNC_INFO;
    emitError( getTokenReply_->errorString() );
    state_ = Empty;
}

void QtOneDrive::slot_refreshTokenFinished()
{
    qDebug() << Q_FUNC_INFO  << getTokenReply_->readAll();
    QJsonObject json = QJsonDocument::fromJson(getTokenReply_->readAll()).object();
    qDebug() << json;
    accessToken_ = json["access_token"].toString();
    authenticationToken_ = json["authentication_token"].toString();
    expiredTokenTime_ = tokenTime_.addSecs( json["expires_in"].toInt() - 60 );
}


void QtOneDrive::slot_singLoadPageSuccess(const QUrl &url)
{
     qDebug() << Q_FUNC_INFO << url;
     QString code = QUrlQuery(url).queryItemValue("code");
     QString errorDesc = QUrlQuery(url).queryItemValue("error_description");

     if( !code.isEmpty() ) {
         closeAuthorizationForm();
         authorizationCode_ = code;
         getToken();
     }
     else
     if( !errorDesc.isEmpty() ) {
          closeAuthorizationForm();
         emitError( errorDesc );
         state_ = Empty;
     }
}

void QtOneDrive::closeAuthorizationForm()
{
    if( AuthorizationForm::isExists() && form_ ) {
        form_->setNeedToClose(true);
        form_ = nullptr;
    }
}

void QtOneDrive::slot_singLoadPageError(const QUrl &url)
{
    closeAuthorizationForm();
    emitError( QString("Could not load page: %1").arg(url.toString()) );
    state_ = Empty;
}

QUrl QtOneDrive::singInUrl() const
{
    QUrl url;
    url.setUrl("https://login.live.com/oauth20_authorize.srf");
    QUrlQuery query;
    query.addQueryItem("client_id", clientID_);
    query.addQueryItem("scope", "wl.signin wl.basic wl.offline_access");
    query.addQueryItem("response_type", "code");
    query.addQueryItem("redirect_uri", redirectURI_ );
    url.setQuery( query );

    return url;
}

QUrl QtOneDrive::singOutUrl() const
{
    QUrl url( "https://login.live.com/oauth20_logout.srf" );
    QUrlQuery query;
    query.addQueryItem("client_id", clientID_);
    query.addQueryItem("redirect_uri", redirectURI_ );
    url.setQuery( query );
    return url;
}

QUrl QtOneDrive::getTokenUrl() const
{
    return QUrl("https://login.live.com/oauth20_token.srf");
}

QUrlQuery QtOneDrive::getTokenPost() const
{
    QUrlQuery query;
    query.addQueryItem("client_id", clientID_);
    query.addQueryItem("redirect_uri", redirectURI_ );
    query.addQueryItem("client_secret", secret_);
    query.addQueryItem("code", authorizationCode_);
    query.addQueryItem("grant_type", "authorization_code" );
    qDebug() << query.toString();
    return query;
}

QUrlQuery QtOneDrive::refreshTokenPost() const
{
    QUrlQuery query;
    query.addQueryItem("client_id", clientID_);
    query.addQueryItem("redirect_uri", redirectURI_ );
    query.addQueryItem("client_secret", secret_);
    query.addQueryItem("refresh_token", authorizationCode_);
    query.addQueryItem("grant_type", "refresh_token" );
    return query;
}

void QtOneDrive::saveProperties()
{
    properties_->setValue("authorization_code", authorizationCode_);
    properties_->setValue("access_token", accessToken_);
    properties_->setValue("authentication_token", authenticationToken_);
    properties_->setValue("expired_token_time", expiredTokenTime_);
    properties_->setValue("is_signin", isSignIn_);
}

void QtOneDrive::loadProperties()
{
    authorizationCode_ = properties_->value("authorization_code", "").toString();
    accessToken_ = properties_->value("access_token", "").toString();
    authenticationToken_ = properties_->value("authentication_token", "").toString();
    expiredTokenTime_ = properties_->value("expired_token_time", QDateTime() ).toDateTime();
    isSignIn_ = properties_->value("is_signin", false).toBool();
}

void QtOneDrive::emitError(const QString &errorDesc)
{
    if( state_ == SingIn ) emit singInError(errorDesc);
    if( state_ == SingOut ) emit singOutError(errorDesc);
    emit error(errorDesc);
}

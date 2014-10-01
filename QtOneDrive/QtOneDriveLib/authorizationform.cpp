#include "authorizationform.h"
#include "ui_authorizationform.h"
#include <QTimer>

bool AuthorizationForm::isExists_ = false;

AuthorizationForm::AuthorizationForm(QWidget *parent, const QUrl &url) :
    QWidget(parent),
    ui(new Ui::AuthorizationForm)
{
    isExists_ = true;
    ui->setupUi(this);
    ui->webView->load( url );
    /*
    QWebSettings::enablePersistentStorage("d:");
    ui->webView->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, false);
    ui->webView->settings()->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
    ui->webView->settings()->setThirdPartyCookiePolicy(QWebSettings::AllowThirdPartyWithExistingCookies);
    ui->webView->settings()->setLocalStoragePath("d:");
    ui->webView->settings()->setOfflineStoragePath("d:");
    ui->webView->settings()->setOfflineStoragePath("d:");
    */

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timer()) );
    timer->setInterval(1000);
    timer->start(2000);
}

AuthorizationForm::~AuthorizationForm()
{
     qDebug() << Q_FUNC_INFO;
    delete ui;
    isExists_ = false;
}

void AuthorizationForm::on_webView_loadFinished(bool arg1)
{
    QUrl url = ui->webView->url();

    if( arg1 )
        emit success( url );
    else
        emit error( url );
}

void AuthorizationForm::on_timer()
{
    if( isNeedToClose_ )
        close();
}

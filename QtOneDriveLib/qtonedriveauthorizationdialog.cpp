#include "qtonedriveauthorizationdialog.h"
#include <QTimer>
#include <QBoxLayout>
#include <QWebView>
#include <QDesktopWidget>
#include <QApplication>
#include <QAction>
#include "qtonedrivewebview.h"

bool QtOneDriveAuthorizationDialog::isExists_ = false;

QtOneDriveAuthorizationDialog::QtOneDriveAuthorizationDialog(const QUrl &url, QWidget *parent) :
    QDialog(parent), url_(url)
{
    setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle( tr("OneDrive Authorization"));
    setMinimumSize( QSize(550, 650) );
    resize( QSize(550, 650) );

    isExists_ = true;

    webView_ = new QtOneDriveWebView(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    this->setLayout( layout);
    layout->addWidget(webView_);


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timer()) );
    timer->setInterval(1000);
    timer->start(1000);

    webView_->load( url );
    connect(webView_,  SIGNAL(loadFinished(bool)), this, SLOT(on_webView_loadFinished(bool)) );
}

QtOneDriveAuthorizationDialog::~QtOneDriveAuthorizationDialog()
{
    isExists_ = false;
}

void QtOneDriveAuthorizationDialog::on_timer()
{
    if( isNeedToClose_ )
        close();
}

void QtOneDriveAuthorizationDialog::on_webView_loadFinished(bool arg1)
{
    QUrl url = webView_->url();

    if( arg1 )
        emit success( url );
    else
        emit error( url );
}

#ifndef AUTHORIZATIONFORM_H
#define AUTHORIZATIONFORM_H

#include <QWidget>

namespace Ui {
class AuthorizationForm;
}

class AuthorizationForm : public QWidget
{
    Q_OBJECT

public:
    explicit AuthorizationForm(QWidget *parent, const QUrl &url);
    ~AuthorizationForm();

    static bool isExists() { return isExists_; }
    void setNeedToClose( bool close ) { isNeedToClose_ = close; }
private slots:
    void on_webView_loadFinished(bool arg1);
    void on_timer();

signals:
    void success( const QUrl &url );
    void error( const QUrl &url);

private:
    Ui::AuthorizationForm *ui;
    static bool isExists_;
    bool isNeedToClose_ = false;
};


#endif // AUTHORIZATIONFORM_H

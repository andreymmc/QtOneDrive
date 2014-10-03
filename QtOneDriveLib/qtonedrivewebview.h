#ifndef QTONEDRIVEWEBVIEW_H
#define QTONEDRIVEWEBVIEW_H

#include <QWebView>

class QtOneDriveWebView : public QWebView
{
    Q_OBJECT
public:
    QtOneDriveWebView(QWidget *parent = 0);
    void contextMenuEvent(QContextMenuEvent *event);
signals:

public slots:

};

#endif // QTONEDRIVEWEBVIEW_H

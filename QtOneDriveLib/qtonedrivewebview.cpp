#include "qtonedrivewebview.h"
#include <QContextMenuEvent>
#include <QMenu>

QtOneDriveWebView::QtOneDriveWebView(QWidget *parent) :
    QWebView(parent)
{

}

void QtOneDriveWebView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu* menu = new QMenu(this);
    menu->addAction(pageAction(QWebPage::Copy));
    menu->addAction(pageAction(QWebPage::Paste));
    menu->exec( mapToGlobal(event->pos()) );
}

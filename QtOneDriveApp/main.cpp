#include <QApplication>
#include <QTimer>
#include <QObject>
#include <QtCore>


#include "testdialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TestDialog dlg;
    dlg.show();
    return a.exec();
}


#include <QApplication>
#include <QTimer>
#include <QObject>
#include <QtCore>


#include "testonedrive.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestOneDrive *test = new TestOneDrive(&a);

    QObject::connect(test, SIGNAL(finished()), &a, SLOT(quit()));
    QTimer::singleShot(100, test, SLOT(run()) );
    return a.exec();
}


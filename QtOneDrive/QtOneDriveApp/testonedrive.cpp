#include "testonedrive.h"
#include "../QtOneDriveLib/qtonedrive.h"

TestOneDrive::TestOneDrive(QObject *parent) :
    QObject(parent)
{

}

TestOneDrive::~TestOneDrive()
{
    qDebug() << Q_FUNC_INFO;
}

void TestOneDrive::run()
{
    oneDrive = new QtOneDrive(  "00000000401165E5",
                                      "KUzoAnuwmvfugJMiAi15E2kjbSY4PAE8",
                                      "http://cloudbackuprobot.com/one-drive.php", "uid", this );

    connect( oneDrive, &QtOneDrive::error, this, &TestOneDrive::onError );
    connect( oneDrive, &QtOneDrive::singInSuccess, this, &TestOneDrive::onSingInSuccess );

    oneDrive->signIn();
}

void TestOneDrive::onError(const QString &errorStr)
{
    qDebug() << "\n\nONE ERROR:" << errorStr << "\n\n";
}

void TestOneDrive::onSingInSuccess()
{
    qDebug() << "onSingInSuccess";
    qDebug() << Q_FUNC_INFO;


}

void TestOneDrive::onSingOutSuccess()
{

}

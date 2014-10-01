#ifndef TESTONEDRIVE_H
#define TESTONEDRIVE_H

#include <QObject>
class QtOneDrive;
class TestOneDrive : public QObject
{
    Q_OBJECT
public:
    explicit TestOneDrive(QObject *parent = 0);
    ~TestOneDrive();


signals:
    void finished();
public slots:
    void run();
    void onError( const QString &errorStr );
    void onSingInSuccess();
    void onSingOutSuccess();
private:
    QtOneDrive *oneDrive;
};

#endif // TESTONEDRIVE_H

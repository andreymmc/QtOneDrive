QtOneDrive
==========

Qt5 API for OneDrive


*Examples:*

**1. SignIn**
```c++
QtOneDrive* oneDrive = new QtOneDrive(YOUR_CLIENT_ID, YOUR_SECRET, ANY_ID, parent );
// or  QtOneDrive* oneDrive = new QtOneDrive(YOUR_CLIENT_ID, YOUR_SECRET, YOUR_REDIRECT_URI,  ANY_ID, parent );

connect( oneDrive, &QtOneDrive::error, [this] (const QString& error)
{
    qDebug() << "ERROR: " << error;
});

connect( oneDrive, &QtOneDrive::successSignIn, [this] ()
{
    qDebug() << "SingIn Success!";
});

oneDrive->singIn();

```

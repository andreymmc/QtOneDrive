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
**2. Upload File**
```C++
QtOneDrive* oneDrive = new QtOneDrive(YOUR_CLIENT_ID, YOUR_SECRET, ANY_ID, parent );

oneDrive->uploadFile("c:\\MyFolder\\MyFile.txt", FOLDER_ID);

connect( oneDrive, &QtOneDrive::error, [this] (const QString& error)
{
    qDebug() << "ERROR: " << error;
});
connect( oneDrive, &QtOneDrive::progressUploadFile, [this] (const QString& filePath, int percent)
{
    qDebug() << QString("Progress %1 %%").arg(percent()l
});
connect( oneDrive, &QtOneDrive::successSignIn, [this] (const QString& filePath, coust QString &fileID)
{
    qDebug() << QString("Upload Success. File Path: %1   File Id: %2").arg(filePath, fileId);
});
```

**3. Download File**

**4. Delete File or Folder**
```c++
...
oneDrive->deleteItem( id );
...
```

**5. Get User Info**
```c++
...
oneDrive->getUserInfo();
...
```

**6. Create Folder**

```c++
...
oneDrive->createFolder("My Folder Name", PARENT_FOLDER_ID);
...
```

**7. Sing Out**
```c++
...
oneDrive->signOut();
...

#ifndef TESTDIALOG_H
#define TESTDIALOG_H

#include <QDialog>

namespace Ui {
class TestDialog;
}

class QtOneDrive;
class TestDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TestDialog(QWidget *parent = 0);
    ~TestDialog();

private slots:
    void on_pushButton_SignIn_clicked();
    void on_pushButton_SingOut_clicked();
    void on_pushButton_GetUserInfo_clicked();

    void on_pushButton_clicked();


    void on_lineEdit_fileID_textChanged(const QString& arg1);

    void on_pushButton_getFiles_clicked();

    void on_pushButton_traserveFolder_clicked();

    void on_pushButton_getFolders_clicked();

    void on_pushButton_downloadFile_clicked();

    void on_pushButton_createFolder_clicked();

    void on_pushButton_deleteFile_clicked();

    void on_pushButton_upload2_clicked();

private:
    Ui::TestDialog *ui;
    QtOneDrive *oneDrive = nullptr;
};

#endif // TESTDIALOG_H

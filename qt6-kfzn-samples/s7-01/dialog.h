#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    // 进度条被取消的槽函数
    void on_progress_canceled();

    void on_btnClearText_clicked();

    void on_btnOpenFile_clicked();

    void on_btnOpenFiles_clicked();

    void on_btnSaveFile_clicked();

    void on_btnSelectExistDir_clicked();

    void on_btnGetColor_clicked();

    void on_btnGetFont_clicked();

    void on_btnProgress_clicked();

    void on_btnInputStr_clicked();

    void on_btnInputInt_clicked();

    void on_btnInputItem_clicked();

    void on_btnInputFloat_clicked();

    void on_btnWarn_clicked();

    void on_btnCritical_clicked();

    void on_btnAbout_clicked();

    void on_btnAboutQt_clicked();

    void on_btnInfo_clicked();

    void on_btnQues_clicked();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H

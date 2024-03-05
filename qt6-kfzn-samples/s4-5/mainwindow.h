#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnLeft_clicked();

    void on_btnMid_clicked();

    void on_btnRight_clicked();

    void on_btnBold_clicked(bool checked);

    void on_btnItalic_clicked(bool checked);

    void on_btnUnderline_clicked(bool checked);

    void on_btnBlack_clicked();

    void on_btnRed_clicked();

    void on_radioButton_3_clicked();

    void on_btnBlue_clicked();

    void on_chkRo_clicked(bool checked);

    void on_chkEnable_clicked(bool checked);

    void on_chkClearBtnEnable_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

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
    void on_dial_valueChanged(int value);

    void on_slider_valueChanged(int value);

    void on_scroll_valueChanged(int value);

    void on_btnPercentage_clicked(bool checked);

    void on_btnPercentage_clicked();

    void on_btnValue_clicked();

    void on_chkTextVisiable_clicked(bool checked);

    void on_chkInverted_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

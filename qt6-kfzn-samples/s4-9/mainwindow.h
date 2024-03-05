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
    void on_btnInitList_clicked();

    void on_btnClearList_clicked();

    void on_chkEdittable_clicked(bool checked);

    void on_btnClear_clicked();

    void on_comboItem_currentTextChanged(const QString &arg1);

    void on_btnInitCity_clicked();

    void on_comboCity_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

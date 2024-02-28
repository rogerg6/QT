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
    void on_ops_pressed();
    void on_clear_pressed();
    void on_calc_pressed();


private:
    Ui::MainWindow *ui;
    QString current_input;

};
#endif // MAINWINDOW_H

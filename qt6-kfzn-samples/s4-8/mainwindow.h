#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>

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

private:
    QTimer *_timer;
    QElapsedTimer _counter;

private slots:
    void do_timer_timeout();
    void do_timer_shot();     // 与单次定时器关联的槽函数
    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_btnDynamic_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

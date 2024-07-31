#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

#include "mythread.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    TDaqThread *threadDaq_;
    TProcessThread *threadProc_;

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void do_thread_started();
    void do_thread_finished();


    void on_actStartThread_triggered();

    void on_actStopThread_triggered();

    void on_actClear_triggered();


    void do_readData(int buf_seq, int *buf, int len);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

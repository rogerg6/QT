#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QTimer>

#include "tdicethread.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    TDiceThread *threadA_;
    QTimer *timer_;

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void do_threadA_started();
    void do_threadA_finished();

    // void do_threadA_newValue(int seq, int dice_value);

    void on_actStartThread_triggered();

    void on_actStart_triggered();

    void on_actPause_triggered();

    void on_actStopThread_triggered();

    void on_actClear_triggered();

    void do_timeOut();


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H

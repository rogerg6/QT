#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

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
    TDiceValThread *threadVal_;
    TDicePicThread *threadPic_;

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void do_threadA_started();
    void do_threadA_finished();


    void on_actStartThread_triggered();

    void on_actStart_triggered();

    void on_actPause_triggered();

    void on_actStopThread_triggered();

    void on_actClear_triggered();


    void do_diceValue(int seq, int dice_value);
    void do_dicePic(const QString filename);



public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

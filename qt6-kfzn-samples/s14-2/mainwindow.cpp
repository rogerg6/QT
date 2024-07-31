#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    threadA_ = new TDiceThread(this);

    ui->actStart->setEnabled(false);
    ui->actPause->setEnabled(false);
    ui->actStopThread->setEnabled(false);

    connect(threadA_, &TDiceThread::started, this, &MainWindow::do_threadA_started);
    connect(threadA_, &TDiceThread::finished, this, &MainWindow::do_threadA_finished);
    // connect(threadA_, &TDiceThread::newValue, this, &MainWindow::do_threadA_newValue);

    timer_ = new QTimer(this);
    timer_->setInterval(200);    // 定时周期是200ms
    timer_->stop();
    connect(timer_, &QTimer::timeout, this, &MainWindow::do_timeOut);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (threadA_->isRunning()) {
        threadA_->terminate();      // 强制中止线程
        threadA_->wait();           // 等待线程退出
    }
    event->accept();
}


void MainWindow::do_timeOut() {
    int seq, dice_val;
    static int prev_seq = -1;
    bool valid = threadA_->readNewValue(seq, dice_val);

    if (valid && prev_seq != seq) {
        QString str = QString::asprintf("第 %d 次投骰子，点数为：%d", seq, dice_val);
        ui->plainTextEdit->appendPlainText(str);
        QString filename = QString::asprintf(":/image/images/d%d.jpg", dice_val);
        QPixmap pic(filename);
        ui->label->setPixmap(pic);
        prev_seq = seq;
    }
}

void MainWindow::do_threadA_started() {
    timer_->start();
    ui->statusbar->showMessage("Thread状态：thread started.");
    ui->actStartThread->setEnabled(false);
    ui->actStart->setEnabled(true);
    ui->actPause->setEnabled(false);
    ui->actStopThread->setEnabled(true);
}

void MainWindow::do_threadA_finished(){
    timer_->stop();
    ui->statusbar->showMessage("Thread状态：thread finished.");
    ui->actStartThread->setEnabled(true);
    ui->actStart->setEnabled(false);
    ui->actPause->setEnabled(false);
    ui->actStopThread->setEnabled(false);
}

// void MainWindow::do_threadA_newValue(int seq, int dice_value) {
//     QString str = QString::asprintf("第 %d 次投骰子，点数为：%d", seq, dice_value);
//     ui->plainTextEdit->appendPlainText(str);
//     QString filename = QString::asprintf(":/image/images/d%d.jpg", dice_value);
//     QPixmap pic(filename);
//     ui->label->setPixmap(pic);
// }

void MainWindow::on_actStartThread_triggered()
{
    threadA_->start();
}


void MainWindow::on_actStart_triggered()
{
    threadA_->diceBegin();
    ui->statusbar->showMessage("Thread状态：thread started.");
    ui->actStart->setEnabled(false);
    ui->actPause->setEnabled(true);
}


void MainWindow::on_actPause_triggered()
{
    threadA_->dicePause();
    ui->statusbar->showMessage("Thread状态：thread started.");
    ui->actStart->setEnabled(true);
    ui->actPause->setEnabled(false);
    QString filename = QString::asprintf(":/image/images/d0.jpg");
    QPixmap pic(filename);
    ui->label->setPixmap(pic);
}


void MainWindow::on_actStopThread_triggered()
{
    threadA_->stopThread();
    QString filename = QString::asprintf(":/image/images/d0.jpg");
    QPixmap pic(filename);
    ui->label->setPixmap(pic);
}


void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}





#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    threadDaq_ = new TDaqThread(this);
    threadProc_ = new TProcessThread(this);


    ui->actStartThread->setEnabled(true);
    ui->actStopThread->setEnabled(false);

    connect(threadDaq_, &TDaqThread::started, this, &MainWindow::do_thread_started);
    connect(threadDaq_, &TDaqThread::finished, this, &MainWindow::do_thread_finished);

    // connect(threadProc_, &TProcessThread::dataAvailable, this, &MainWindow::do_readData);
    connect(threadProc_, &TProcessThread::dataAvailable, this, &MainWindow::do_readData,
                    Qt::BlockingQueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (threadDaq_->isRunning()) {
        threadDaq_->terminate();      // 强制中止线程
        threadDaq_->wait();           // 等待线程退出
    }
    if (threadProc_->isRunning()) {
        threadProc_->terminate();      // 强制中止线程
        threadProc_->wait();           // 等待线程退出
    }
    event->accept();
}

void MainWindow::do_thread_started() {
    ui->statusbar->showMessage("Thread状态：thread started.");
    ui->actStartThread->setEnabled(false);
    ui->actStopThread->setEnabled(true);
}

void MainWindow::do_thread_finished() {
    ui->statusbar->showMessage("Thread状态：thread finished.");
    ui->actStartThread->setEnabled(true);
    ui->actStopThread->setEnabled(false);
}

void MainWindow::do_readData(int buf_seq, int *buf, int len) {

    QString str = QString::asprintf("第 %d 个缓冲区： ", buf_seq);
    for (int i = 0; i < len; i++)
        str += QString::asprintf("%d ", buf[i]);
    ui->plainTextEdit->appendPlainText(str);
    ui->plainTextEdit->appendPlainText("");
}


void MainWindow::on_actStartThread_triggered()
{
    if (!threadProc_->isRunning())
        threadProc_->start();

    threadDaq_->start();
}


void MainWindow::on_actStopThread_triggered()
{
    threadDaq_->stopThread();
}


void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}





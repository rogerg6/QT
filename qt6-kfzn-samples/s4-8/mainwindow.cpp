#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _timer = new QTimer(this);
    _timer->stop();
    _timer->setTimerType(Qt::CoarseTimer);
    ui->radioCoarse->setChecked(true);
    connect(_timer, SIGNAL(timeout()), this, SLOT(do_timer_timeout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_timer_timeout() {
    QTime curtime = QTime::currentTime();

    ui->lcdhour->display(curtime.hour());
    ui->lcdmin->display(curtime.minute());
    ui->lcdsec->display(curtime.second());

    if (_timer->isSingleShot()) {
        int ms = _counter.elapsed();
        QString str = QString("流逝的时间：%1 ms").arg(ms);
        ui->labElapsed->setText(str);

        ui->btnStart->setEnabled(true);
        ui->btnDynamic->setEnabled(true);
        ui->btnStop->setEnabled(false);
    }

}

void  MainWindow::do_timer_shot()  {
    // 与单次定时器关联的槽函数
    int ms = _counter.elapsed();
    int seconds = ms / 1000;
    ms = ms % 1000;
    QString str = QString("流逝的时间：%1 s, %2 ms").arg(seconds).arg(ms);
    ui->labElapsed->setText(str);
    ui->btnDynamic->setEnabled(true);
}

void MainWindow::on_btnStart_clicked()
{
    _timer->setInterval(ui->spinBox->value());

    // 连续触发还是单次触发
    if (ui->radioContinue->isChecked())
        _timer->setSingleShot(false);
    else
        _timer->setSingleShot(true);

    // 定时器精度
    if (ui->radioPrecise->isChecked())
        _timer->setTimerType(Qt::PreciseTimer);
    else if (ui->radioCoarse->isChecked())
        _timer->setTimerType(Qt::CoarseTimer);
    else
        _timer->setTimerType(Qt::VeryCoarseTimer);

    _timer->start();
    _counter.start();

    ui->btnStart->setEnabled(false);
    ui->btnDynamic->setEnabled(false);
    ui->btnStop->setEnabled(true);
}


void MainWindow::on_btnStop_clicked()
{
    _timer->stop();


    int ms = _counter.elapsed();
    int seconds = ms / 1000;
    ms = ms % 1000;
    QString str = QString("流逝的时间：%1 s, %2 ms").arg(seconds).arg(ms);
    ui->labElapsed->setText(str);




    ui->btnStart->setEnabled(true);
    ui->btnDynamic->setEnabled(true);
    ui->btnStop->setEnabled(false);


}


void MainWindow::on_btnDynamic_clicked()
{
    int intv = ui->spinBox->value();
    QTimer::singleShot(intv, Qt::PreciseTimer, this, &MainWindow::do_timer_shot);
    _counter.start();
    ui->btnDynamic->setEnabled(false);
}


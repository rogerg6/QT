#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnRead_clicked()
{
    QDateTime current = QDateTime::currentDateTime();
    ui->timeEdit->setTime(current.time());
    ui->lineEditTime->setText(current.toString("hh : mm : ss"));

    ui->dateEdit->setDate(current.date());
    ui->lineEditDate->setText(current.toString("yyyy-MM-dd"));

    ui->dateTimeEdit->setDateTime(current);
    ui->lineEditDateTime->setText(current.toString("yyyy-MM-dd hh:mm:ss"));
}



void MainWindow::on_calendar_selectionChanged()
{
    QDate date = ui->calendar->selectedDate();
    QString dt = date.toString("yyyy年MM月dd日");
    ui->lineEditChoiceDate->setText(dt);
}


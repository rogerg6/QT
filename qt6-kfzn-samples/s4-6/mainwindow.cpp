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

void MainWindow::on_dial_valueChanged(int value)
{
    ui->progressBar->setValue(value);
}


void MainWindow::on_slider_valueChanged(int value)
{
    ui->progressBar->setValue(value);
}


void MainWindow::on_scroll_valueChanged(int value)
{
    ui->progressBar->setValue(value);
}


void MainWindow::on_btnPercentage_clicked(bool checked)
{

}


void MainWindow::on_btnPercentage_clicked()
{
    ui->progressBar->setFormat("%p%");
}


void MainWindow::on_btnValue_clicked()
{
    ui->progressBar->setFormat("%v");
}


void MainWindow::on_chkTextVisiable_clicked(bool checked)
{
    ui->progressBar->setTextVisible(checked);
}


void MainWindow::on_chkInverted_clicked(bool checked)
{
    ui->progressBar->setInvertedAppearance(checked);
}


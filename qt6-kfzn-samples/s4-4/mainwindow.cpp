#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->spinBoxQuant, SIGNAL(valueChanged(int)), this, SLOT(on_btnCalc_clicked()));
    connect(ui->spinBoxPrice, SIGNAL(valueChanged(double)), this, SLOT(on_btnCalc_clicked()));
    ui->spinBoxTotal->setMaximum(1000000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnCalc_clicked()
{
    double quant = ui->spinBoxQuant->value();
    double price = ui->spinBoxPrice->value();
    ui->spinBoxTotal->setValue(quant * price);
}


void MainWindow::on_spinBoxDec_valueChanged(int arg1)
{
    qDebug(ui->spinBoxDec->cleanText().toLocal8Bit().data());
    ui->spinBoxBin->setValue(arg1);
    ui->spinBoxHex->setValue(arg1);
}


void MainWindow::on_spinBoxBin_valueChanged(int arg1)
{
    qDebug(ui->spinBoxBin->cleanText().toLocal8Bit().data());
    ui->spinBoxDec->setValue(arg1);
    ui->spinBoxHex->setValue(arg1);
}


void MainWindow::on_spinBoxHex_valueChanged(int arg1)
{
    qDebug(ui->spinBoxHex->cleanText().toLocal8Bit().data());
    ui->spinBoxDec->setValue(arg1);
    ui->spinBoxBin->setValue(arg1);
}


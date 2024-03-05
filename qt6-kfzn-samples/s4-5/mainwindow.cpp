#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("Hello");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnLeft_clicked()
{
    ui->lineEdit->setAlignment(Qt::AlignLeft);
}


void MainWindow::on_btnMid_clicked()
{
    ui->lineEdit->setAlignment(Qt::AlignCenter);
}


void MainWindow::on_btnRight_clicked()
{
    ui->lineEdit->setAlignment(Qt::AlignRight);
}


void MainWindow::on_btnBold_clicked(bool checked)
{
    QFont font = ui->lineEdit->font();
    font.setBold(checked);
    ui->lineEdit->setFont(font);
}


void MainWindow::on_btnItalic_clicked(bool checked)
{
    QFont font = ui->lineEdit->font();
    font.setItalic(checked);
    ui->lineEdit->setFont(font);
}


void MainWindow::on_btnUnderline_clicked(bool checked)
{
    QFont font = ui->lineEdit->font();
    font.setUnderline(checked);
    ui->lineEdit->setFont(font);
}


void MainWindow::on_btnBlack_clicked()
{
    QPalette p = ui->btnBlack->palette();
    p.setColor(QPalette::Text, Qt::black);
    ui->lineEdit->setPalette(p);
}


void MainWindow::on_btnRed_clicked()
{
    QPalette p = ui->btnBlack->palette();
    p.setColor(QPalette::Text, Qt::red);
    ui->lineEdit->setPalette(p);
}



void MainWindow::on_radioButton_3_clicked()
{
    QPalette p = ui->btnBlack->palette();
    p.setColor(QPalette::Text, Qt::blue);
    ui->lineEdit->setPalette(p);
}


void MainWindow::on_chkRo_clicked(bool checked)
{
    ui->lineEdit->setReadOnly(checked);
}


void MainWindow::on_chkEnable_clicked(bool checked)
{
    ui->lineEdit->setEnabled(checked);
}


void MainWindow::on_chkClearBtnEnable_clicked(bool checked)
{
    ui->lineEdit->setClearButtonEnabled(checked);
}

void MainWindow::on_btnBlue_clicked(){}


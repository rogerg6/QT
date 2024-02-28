#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

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

void MainWindow::on_pushButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("Open Image"), \
                                                    QDir::homePath(),tr("(*.jpg)\n(*.bmp)\n(*.png)"));
    qDebug()<<"filename:"<<filename;
    QImage image=QImage(filename); //图片初始化
    qDebug()<<"image:"<<image;
    if(!image.isNull()){
        ui->statusbar->showMessage(tr("Open Image Success!"),3000);
    }
    else{
        ui->statusbar->showMessage(tr("Save Image Failed!"),3000);
        return;
    }

    QImage image2=image.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio); //图片缩放
    ui->label->setPixmap(QPixmap::fromImage(image2)); //显示图片
}


void MainWindow::on_pushButton_2_clicked()
{
    qDebug()<<"test is clicked.";
}


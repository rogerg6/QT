#include "window.h"
#include "ui_window.h"
#include <QFileDialog>
#include <QDebug>

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
}

Window::~Window()
{
    delete ui;
}

void Window::on_btnOpen_clicked()
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

    QImage image2=image.scaled(ui->lab_img->width(),ui->lab_img->height(),Qt::KeepAspectRatio); //图片缩放
    ui->lab_img->setPixmap(QPixmap::fromImage(image2)); //显示图片
}


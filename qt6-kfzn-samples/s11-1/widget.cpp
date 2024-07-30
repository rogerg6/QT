#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QString str = QString::asprintf("当前电量：%d %%", ui->battery->powerLevel());
    ui->label->setText(str);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_horizontalSlider_valueChanged(int value)
{
    ui->battery->setPowerLevel(value);
    QString str = QString::asprintf("当前电量：%d %%", value);
    ui->label->setText(str);
}


#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_horizontalSlider_valueChanged(int value)
{
    ui->battery->setPowerLevel(value);
}


void Widget::on_battery_powerLevelChanged(int pow)
{
    QString str = QString::asprintf("当前电量：%d %%", pow);
    ui->label->setText(str);
}


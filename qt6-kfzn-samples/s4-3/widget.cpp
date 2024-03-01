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

void Widget::on_btn_calcTot_clicked()
{
    double quant = ui->lineEditQant->text().toDouble();
    double price = ui->lineEditPrice->text().toDouble();

    QString val;
    val = val.setNum(quant * price, 'f', 2); // 2位小数
    ui->lineEditTotalPrice->setText(val);
}


void Widget::on_btnDec_clicked()
{
    unsigned int num = ui->lineEdit10->text().toUInt();
    QString str = QString::number(num, 16);
    str = str.toUpper();
    ui->lineEdit16->setText(str);
    str = QString::number(num, 2);
    ui->lineEdit2->setText(str);
}

void Widget::on_btnBin_clicked()
{
    bool ok;
    unsigned int num = ui->lineEdit2->text().toUInt(&ok, 2);
    if (!ok){
        ui->lineEdit16->setText("Failed");
        ui->lineEdit10->setText("Failed");
        return;
    }
    QString str = QString::number(num, 16);
    str = str.toUpper();
    ui->lineEdit16->setText(str);
    str = QString::number(num, 10);
    ui->lineEdit10->setText(str);

}


void Widget::on_btnHex_clicked()
{
    bool ok;
    unsigned int num = ui->lineEdit16->text().toUInt(&ok, 16);
    if (!ok){
        ui->lineEdit2->setText("Failed");
        ui->lineEdit10->setText("Failed");
        return;
    }
    QString str = QString::number(num, 2);
    ui->lineEdit2->setText(str);
    str = QString::number(num, 10);
    ui->lineEdit10->setText(str);


}


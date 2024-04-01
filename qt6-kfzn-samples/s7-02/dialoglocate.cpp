#include "dialoglocate.h"
#include "ui_dialoglocate.h"

#include <QMessageBox>
#include <QCloseEvent>
#include <QShowEvent>

DialogLocate::DialogLocate(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogLocate)
{
    ui->setupUi(this);
}

DialogLocate::~DialogLocate()
{
    QMessageBox::information(this,"提示","TDialogLocate 对话框被删除");
    delete ui;
}

void DialogLocate::on_btnSetText_clicked()
{
    int row = ui->spinRowNum->value();
    int col = ui->spinColNum->value();
    QString txt = ui->lineEdit->text();
    emit changeCellText(row, col, txt);

    // 行增：设置完当前(r,c)后，r+=1, 列增同理
    if (ui->chkRowAdd->isChecked())
        ui->spinRowNum->setValue(1 + ui->spinRowNum->value());
    // 列增
    if (ui->chkColAdd->isChecked())
        ui->spinColNum->setValue(1 + ui->spinColNum->value());
}

void DialogLocate::closeEvent(QCloseEvent *event) {
    event->accept();
    emit changeActionEnable(true);
}


void DialogLocate::showEvent(QShowEvent *event) {
    event->accept();
    emit changeActionEnable(true);
}

void DialogLocate::setSpinRange(int row_cnt, int col_cnt){
    ui->spinRowNum->setMaximum(row_cnt);
    ui->spinColNum->setMaximum(col_cnt);
}

void DialogLocate::setSpinValue(int row_no, int col_no){
    ui->spinRowNum->setValue(row_no);
    ui->spinColNum->setValue(col_no);
}




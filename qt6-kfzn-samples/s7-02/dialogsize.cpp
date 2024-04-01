#include "dialogsize.h"
#include "ui_dialogsize.h"

#include <QMessageBox>

DialogSize::DialogSize(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogSize)
{
    ui->setupUi(this);
}

DialogSize::~DialogSize()
{
    QMessageBox::information(this, "提示", "DialogSize对话框被删除");
    delete ui;
}

int DialogSize::rowCount() {
    return ui->spinRows->value();
}


int DialogSize::columnCount(){
    return ui->spinCols->value();
}


void DialogSize::setRowColumn(int row, int column) {
    ui->spinRows->setValue(row);
    ui->spinCols->setValue(column);
}


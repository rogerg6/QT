#include "dialogheaders.h"
#include "ui_dialogheaders.h"

#include <QMessageBox>

DialogHeaders::DialogHeaders(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogHeaders)
{
    ui->setupUi(this);
    model_ = new QStringListModel(this);
    ui->listView->setModel(model_);
}

DialogHeaders::~DialogHeaders()
{
    QMessageBox::information(this, "提示", "DialogHeader对话框被删除");
    delete ui;
}

void DialogHeaders::setHeaderList(QStringList &header) {
    model_->setStringList(header);
}


QStringList DialogHeaders::headerList() {
    return model_->stringList();
}

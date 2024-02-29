#include "window.h"
#include "ui_widget.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Window::~Window()
{
    delete ui;
}

void Window::on_btnCharJudge_clicked()
{
    QString str = ui->editChar->text();
    QChar ch = str[0];

    char16_t unicode = ch.unicode();
    QString info = str+ QString::asprintf("\t,Unicode编码= 0x%X",unicode);
    ui->plainTextEdit->appendPlainText(info);

    ui->chkDigit->setChecked(ch.isDigit()); //是否为数字0~9
    ui->chkLetter->setChecked(ch.isLetter());   //是否为字母
    ui->chkLetterOrNumber->setChecked(ch.isLetterOrNumber());   //是否为数字或字母
    ui->chkUpper->setChecked(ch.isUpper());     //是否为大写
    ui->chkLower->setChecked(ch.isLower());     //是否为小写
    ui->chkMark->setChecked(ch.isMark());       //是否为符号
    ui->chkSpace->setChecked(ch.isSpace());     //是否为空格
    ui->chkSymbol->setChecked(ch.isSymbol());   //是否为符号
    ui->chkPunct->setChecked(ch.isPunct());     //是否为标点符号

}


void Window::on_btnGetChars_clicked()
{
    QString str = ui->editStr->text();

    for (qint16 i = 0; i < str.size(); i++){
        QChar ch = str[i];
        char16_t unicode = ch.unicode();
        QString info = ch + QString::asprintf("\t,Unicode编码= 0x%X",unicode);
        ui->plainTextEdit->appendPlainText(info);

    }
}


void Window::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}


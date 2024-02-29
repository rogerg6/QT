#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
    ui->plainTextEdit->setPlainText("你好QT！！！");

    connect(ui->radioBlack, SIGNAL(clicked()), this, SLOT(do_setFontColor()));
    connect(ui->radioRed, SIGNAL(clicked()), this, SLOT(do_setFontColor()));
    connect(ui->radioBlue, SIGNAL(clicked()), this, SLOT(do_setFontColor()));
}

Window::~Window()
{
    delete ui;
}

void Window::do_setFontColor() {
    QPalette plet = ui->plainTextEdit->palette();
    if (ui->radioBlack->isChecked())
        plet.setColor(QPalette::Text, Qt::black);
    else if (ui->radioRed->isChecked())
        plet.setColor(QPalette::Text, Qt::red);
    else if (ui->radioBlue->isChecked())
        plet.setColor(QPalette::Text, Qt::blue);

    ui->plainTextEdit->setPalette(plet);
}

void Window::on_chkBoxUnderline_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();
    font.setUnderline(checked);
    ui->plainTextEdit->setFont(font);
}


void Window::on_chkBoxItalic_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();
    font.setItalic(checked);
    ui->plainTextEdit->setFont(font);
}


void Window::on_chkBoxBold_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();
    font.setBold(checked);
    ui->plainTextEdit->setFont(font);
}

void Window::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}


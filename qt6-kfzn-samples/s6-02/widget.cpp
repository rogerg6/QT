#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->lab, SIGNAL(doubleClicked()), this, SLOT(do_doubleClicked()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event){
    Q_UNUSED(event);
    ui->lab->setText("窗口被点击了");
    ui->lab->adjustSize();
}


void Widget::do_doubleClicked(){
    ui->lab->setText("标签被点击了，信号槽函数响应");
    ui->lab->adjustSize();
}

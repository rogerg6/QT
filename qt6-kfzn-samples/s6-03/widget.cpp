#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 安装事件过滤器，把lab1、lab2的事件派发给this处理
    ui->lab1->installEventFilter(this);
    ui->lab2->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *watched, QEvent *event){
    if (watched == ui->lab1) {
        if (event->type() == QEvent::Enter)
            ui->lab1->setStyleSheet("background-color: rgb(170, 255, 255);");
        else if (event->type() == QEvent::Leave) {
            ui->lab1->setStyleSheet("");
            ui->lab1->setText("靠近我，点击我");
        }
        else if (event->type() == QEvent::MouseButtonPress)
            ui->lab1->setText("button pressed");
        else if (event->type() == QEvent::MouseButtonRelease)
            ui->lab1->setText("button released");
    } else if (watched == ui->lab2) {
        if (event->type() == QEvent::Enter)
            ui->lab2->setStyleSheet("background-color: rgb(85, 255, 127);");
        else if (event->type() == QEvent::Leave) {
            ui->lab2->setStyleSheet("");
            ui->lab2->setText("可双击的标签");
         }
        else if (event->type() == QEvent::MouseButtonDblClick)
            ui->lab2->setText("double clicked");
    }

    return QWidget::eventFilter(watched, event);

    /**
     * 如果直接返回true，则事件过滤器拦截的事件将不会传播给被监视对象，
     * 那就只能处理这里定义的几个事件，所以应该调用父类的eventFilter
     */
    // return true;
}

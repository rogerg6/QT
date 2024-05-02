#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QPaintEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white));    // 设置窗口为白色背景
    setAutoFillBackground(true);
    this->resize(400,300);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    int w = this->width();
    int h = this->height();
    QRect rect(w/4, h/4,w/2,h/2);

    // set pen
    QPen pen;
    pen.setWidth(3);                    // 线宽
    pen.setColor(Qt::red);              // 线条颜色
    pen.setStyle(Qt::SolidLine);        // 线条样式
    pen.setCapStyle(Qt::FlatCap);       // 线条端点样式
    pen.setJoinStyle(Qt::BevelJoin);    // 线条连接样式
    painter.setPen(pen);

    // set brush
    QBrush brush;
    brush.setColor(Qt::yellow);         // 画刷颜色
    brush.setStyle(Qt::SolidPattern);   // 画刷填充样式
    painter.setBrush(brush);

    // 绘图
    painter.drawRect(rect);
    event->accept();
}

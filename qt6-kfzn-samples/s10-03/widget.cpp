#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QLinearGradient>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    resize(300,300);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    int w = width();
    int h = height();
    int side = qMin(w, h);
    QRect rect((w-side)/2, (h-side)/2, side, side);
    p.drawRect(rect);
    p.setViewport(rect);            // 设置视口
    p.setWindow(-100,-100,200,200); // 设置窗口

    // 设置画笔
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);
    p.setPen(pen);

    // 线性渐变
    QLinearGradient linear_grad(0,0,100,0);     // 从左到右
    linear_grad.setColorAt(0, Qt::yellow);      // 起点颜色
    linear_grad.setColorAt(1, Qt::green);       // 终点颜色
    linear_grad.setSpread(QGradient::PadSpread);    // 展布模式
    p.setBrush(linear_grad);

    // 设置组合模式
    p.setCompositionMode(QPainter::CompositionMode_Difference);

    for (int i = 0; i < 36; i++) {
        p.drawEllipse(QPoint(50, 0), 50, 50);
        p.rotate(10);

    }

    event->accept();
}


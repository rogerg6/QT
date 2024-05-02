#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPainterPath>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    resize(600,300);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::TextAntialiasing);

    // 生成五角星的5个顶点，假设原点在五角星中心
    qreal R=100;
    const qreal Pi = 3.14159;
    qreal deg = Pi * 72 /180;

    QPoint points[5] = {
        QPoint(R, 0),
        QPoint(R*qCos(deg), -R*qSin(deg)),
        QPoint(R*qCos(2*deg), -R*qSin(2*deg)),
        QPoint(R*qCos(3*deg), -R*qSin(3*deg)),
        QPoint(R*qCos(4*deg), -R*qSin(4*deg)),
    };

    // 设置字体
    QFont font;
    font.setPointSize(14);
    p.setFont(font);

    // 设置画笔
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::blue);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);
    p.setPen(pen);

    // 设置画刷
    QBrush brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);
    p.setBrush(brush);

    // 设置绘制五角星的PainterPath, 以便复用
    QPainterPath star_path;
    star_path.moveTo(points[0]);
    star_path.lineTo(points[2]);
    star_path.lineTo(points[4]);
    star_path.lineTo(points[1]);
    star_path.lineTo(points[3]);
    star_path.closeSubpath();       // 闭合路径，最后一个点与第一个点相连
    star_path.addText(points[0], font, "1");
    star_path.addText(points[1], font, "2");
    star_path.addText(points[2], font, "3");
    star_path.addText(points[3], font, "4");
    star_path.addText(points[4], font, "5");

    // 绘图。第一个五角星
    p.save();                   // push 坐标状态
    p.translate(100,120);       // 平移
    p.drawPath(star_path);
    p.drawText(0,0,"S1");
    p.restore();                // pop 坐标状态

    // 第二个五角星
    p.translate(300,120);
    p.scale(0.8, 0.8);          // 缩放
    p.rotate(90);               // 顺时针旋转90°
    p.drawPath(star_path);
    p.drawText(0,0,"S2");

    // 第三个五角星
    p.resetTransform();         // 复位所有的坐标变换
    p.translate(500,120);
    p.rotate(-145);             // 逆时针旋转145°
    p.drawPath(star_path);
    p.drawText(0,0,"S3");

    event->accept();
}

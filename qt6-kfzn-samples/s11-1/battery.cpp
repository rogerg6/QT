#include "battery.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPaintEvent>

Battery::Battery(QWidget *parent) : QWidget{parent}
{
    //    setPalette(QPalette(mColorBack));
    //    setAutoFillBackground(true);
    //    this->resize(120,50);
}

void Battery::paintEvent(QPaintEvent *event){
    // 绘制界面组件
    QPainter painter(this);
    QRect rect(0, 0, width(), height());   // 视口矩形区
    painter.setViewport(rect);             // 设置视口
    painter.setWindow(0, 0, 120, 50);      // 设置窗口大小，逻辑坐标
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    // 绘制边框
    QPen pen(border_clr);
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);
    painter.setPen(pen);

    QBrush brush(back_clr);
    brush.setStyle(Qt::SolidPattern);

    painter.setBrush(brush);
    rect.setRect(1,1,109,48);
    painter.drawRect(rect);           // 电池边框

    brush.setColor(border_clr);
    painter.setBrush(brush);
    rect.setRect(110, 15, 10, 20);
    painter.drawRect(rect);           // 电池头

    // 绘制电量柱
    if (power_level_ > warn_level_){
        pen.setColor(power_clr);
        brush.setColor(power_clr);
    } else {
        pen.setColor(warn_clr);
        brush.setColor(warn_clr);
    }
    painter.setPen(pen);
    painter.setBrush(brush);
    if (power_level_ > 0) {
        rect.setRect(5,5, power_level_, 40);
        painter.drawRect(rect);
    }

    // 绘制百分比
    QFontMetrics text_size(this->font());
    QString pow_str = QString::asprintf("%d%%", power_level_);
    QRect text_rect = text_size.boundingRect(pow_str);
    painter.setFont(this->font());
    pen.setColor(border_clr);
    painter.setPen(pen);
    painter.drawText(55 - text_rect.width()/2, 23 + text_rect.height()/2, pow_str);

    event->accept();
}

void Battery::setPowerLevel(int pow){
    power_level_ = pow;
    emit powerLevelChanged(pow);
    repaint();
}

int Battery::powerLevel() { return power_level_; }

void Battery::setWarnLevel(int warn) {
    warn_level_ = warn;
    repaint();
}

int Battery::warnLevel() { return warn_level_; }

QSize Battery::sizeHint() {
    int H = this->height();
    int W = H * 12 / 5;
    QSize size(W, H);
    return size;
}



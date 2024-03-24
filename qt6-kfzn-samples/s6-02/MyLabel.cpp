#include "MyLabel.h"

MyLabel::MyLabel(QWidget *parent)
    : QLabel(parent) {
    this->setAttribute(Qt::WA_Hover, true);     // 必须设置此属性，才能产生hover事件
}


bool MyLabel::event(QEvent *e) {
    if (e->type() == QEvent::HoverEnter) {
        QPalette plt = this->palette();
        plt.setColor(QPalette::WindowText, Qt::red);
        this->setPalette(plt);
    } else if (e->type() == QEvent::HoverLeave) {
        QPalette plt = this->palette();
        plt.setColor(QPalette::WindowText, Qt::black);
        this->setPalette(plt);
    }

    // 运行父类event，处理其他事件
    return QLabel::event(e);
}


void MyLabel::mouseDoubleClickEvent(QMouseEvent *event){
    Q_UNUSED(event);
    emit doubleClicked();
}


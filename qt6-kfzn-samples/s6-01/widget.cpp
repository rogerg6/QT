#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(),
                       QPixmap(":/pics/images/background.jpg"));
}
void Widget::closeEvent(QCloseEvent *event){
    QString dlg_title = "消息框";
    QString info = "确定要退出吗？";
    QMessageBox::StandardButton result = QMessageBox::question(this, dlg_title, info,
                         QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if (result == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}
void Widget::keyPressEvent(QKeyEvent *event){
    QPoint pt = ui->btn->pos();

    if (event->key() == Qt::Key_A)
        ui->btn->move(pt.x() - 20, pt.y());
    else if (event->key() == Qt::Key_D)
        ui->btn->move(pt.x() + 20, pt.y());
    else if (event->key() == Qt::Key_W)
        ui->btn->move(pt.x(), pt.y() - 20);
    else if (event->key() == Qt::Key_S)
        ui->btn->move(pt.x(), pt.y() + 20);

    event->accept();
}
void Widget::showEvent(QShowEvent *event){
    Q_UNUSED(event);
    qDebug("showEvent() 被触发");
}
void Widget::hideEvent(QHideEvent *event){
    Q_UNUSED(event);
    qDebug("hideEvent() 被触发");
}


void Widget::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        QPoint pt = event->pos();       // 点击点在窗口上的相对坐标
        QPointF rela_pt = event->position();    // 相对坐标
        QPointF win_pt = event->scenePosition();    // 相对坐标
        QPointF glob_pt = event->globalPosition();  // 屏幕或虚拟桌面上的绝对坐标

        QString str = QString::asprintf("pos() = (%d, %d)", pt.x(), pt.y());
        str += QString::asprintf("\nposition() = (%.0f, %.0f)", rela_pt.x(), rela_pt.y());
        str += QString::asprintf("\nscenePosition() = (%.0f, %.0f)", win_pt.x(), win_pt.y());
        str += QString::asprintf("\nglobalPosition() = (%.0f, %.0f)", glob_pt.x(), glob_pt.y());

        ui->lab->setText(str);
        ui->lab->adjustSize();      // 自动调整组件大小
        ui->lab->move(pt);
    }
    QWidget::mousePressEvent(event);
}

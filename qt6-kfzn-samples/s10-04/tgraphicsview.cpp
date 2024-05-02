#include "tgraphicsview.h"

TGraphicsView::TGraphicsView(QWidget *parent) {}

void TGraphicsView::mouseMoveEvent(QMouseEvent *event) {
    QPoint point = event->pos();            // 视图中的坐标
    emit mouseMovePoint(point);             // 发射信号
    QGraphicsView::mouseMoveEvent(event);
}

void TGraphicsView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QPoint point = event->pos();        // 视图中的坐标
        emit mouseClicked(point);
    }
    QGraphicsView::mousePressEvent(event);
}

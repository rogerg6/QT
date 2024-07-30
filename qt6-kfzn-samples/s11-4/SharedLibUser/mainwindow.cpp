#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tpendialog.h"

#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QRect rect(0, 0, width(), height());
    painter.setViewport(rect);
    painter.setWindow(0, 0, 100, 50);
    painter.setPen(pen_);
    painter.drawRect(10, 10, 80, 30);
    event->accept();
}

void MainWindow::on_action_Pen_triggered()
{
    bool ok = false;
    QPen pen = TPenDialog::getPen(pen_, &ok);
    if (ok) {
        pen_ = pen;
        this->repaint();
    }
}


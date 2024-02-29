#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJSEngine>
#include <QJSValue>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton *btn;
    for (int i = 0; i < 10; i++){
        QString btn_name = "bt" + QString::number(i);
        btn = MainWindow::findChild<QPushButton*>(btn_name);
        connect(btn, SIGNAL(clicked()), this, SLOT(on_ops_pressed()));
    }
    QString op_btn_names[] = {"bt_add", "bt_minus", "bt_mul", "bt_div", "btn_leftbrace", "btn_rightbrace"};
    for (int i = 0; i < 6; i++){
        btn = MainWindow::findChild<QPushButton*>(op_btn_names[i]);
        connect(btn, SIGNAL(clicked()), this, SLOT(on_ops_pressed()));
    }

    QString btcalc_name = "bt_calc";
    btn = MainWindow::findChild<QPushButton*>(btcalc_name);
    connect(btn, SIGNAL(clicked()), this, SLOT(on_calc_pressed()));
    QString btclr_name = "bt_clr";
    btn = MainWindow::findChild<QPushButton*>(btclr_name);
    connect(btn, SIGNAL(clicked()), this, SLOT(on_clear_pressed()));

    current_input = "";
    ui->input->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ops_pressed()
{
    QPushButton *btn = (QPushButton*)sender();

    QString val = btn->text();
    current_input += val;
    ui->input->setText(current_input);
}


void MainWindow::on_clear_pressed(){
    qDebug() << "clear button clicked";
    current_input = "";
    ui->input->clear();
}

void MainWindow::on_calc_pressed(){
    qDebug() << "calc button clicked";

    QJSEngine myEngine;
    QJSValue res = myEngine.evaluate(ui->input->text());
    if (res.isError()) {
        res = QJSValue("Invalid expression");
    }
    ui->input->setText(res.toString());
    current_input = "";
}

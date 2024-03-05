#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_btnInitList_clicked()
{
    QIcon icon;

    icon.addFile(":/icons/aim.ico");
    ui->comboItem->clear();
    for (int i = 0; i < 15; i++) {
        ui->comboItem->addItem(icon, QString("Item %1").arg(i));
    }
}


void MainWindow::on_btnClearList_clicked()
{
    ui->comboItem->clear();
}


void MainWindow::on_chkEdittable_clicked(bool checked)
{
    ui->comboItem->setEditable(checked);
}


void MainWindow::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}


void MainWindow::on_comboItem_currentTextChanged(const QString &arg1)
{
    ui->plainTextEdit->appendPlainText(arg1);
}


void MainWindow::on_btnInitCity_clicked()
{
    QMap<QString, int> city_zone;
    city_zone.insert("北京",10);
    city_zone.insert("上海",21);
    city_zone.insert("天津",22);
    city_zone.insert("大连",411);
    city_zone.insert("锦州",416);
    city_zone.insert("徐州",516);
    city_zone.insert("福州",591);
    city_zone.insert("青岛",532);

    ui->comboCity->clear();
    foreach(const QString &city, city_zone.keys())
        ui->comboCity->addItem(city, city_zone.value(city));
}


void MainWindow::on_comboCity_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    QString city = ui->comboCity->currentText();
    QString zone = ui->comboCity->currentData().toString();
    ui->plainTextEdit->appendPlainText(QString("%1 + 区号= %2").arg(city).arg(zone));
}


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter);

    str_list_ << "北京" << "上海" << "天津" << "河北" << "山东" << "四川" << "重庆" << "广东" << "河南" ;
    model_ = new QStringListModel(this);
    model_->setStringList(str_list_);
    ui->listView->setModel(model_);
    ui->chkEditable->setChecked(true);
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_chkEditable_clicked(bool checked)
{
    if (checked) {
        ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    }else {
        ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}


void MainWindow::on_btnRestoreList_clicked()
{
    model_->setStringList(str_list_);
}


void MainWindow::on_btnClearList_clicked()
{
    model_->removeRows(0, model_->rowCount());
}


void MainWindow::on_btnAddItem_clicked()
{
    model_->insertRow(model_->rowCount());
    QModelIndex index = model_->index(model_->rowCount()-1, 0);
    model_->setData(index, "New Item", Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}


void MainWindow::on_btnInsertItem_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    model_->insertRow(index.row());
    model_->setData(index, "Insert Item", Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}


void MainWindow::on_btnDelItem_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    model_->removeRow(index.row());
}


void MainWindow::on_btnMoveUp_clicked()
{
    int cur_row = ui->listView->currentIndex().row();
    QModelIndex index = QModelIndex();
    model_->moveRow(index, cur_row, index, cur_row-1);
}


void MainWindow::on_btnMoveDown_clicked()
{
    int cur_row = ui->listView->currentIndex().row();
    QModelIndex index = QModelIndex();
    model_->moveRow(index, cur_row, index, cur_row+2);
}


void MainWindow::on_btnSort_clicked(bool checked)
{
    if (checked)
        model_->sort(0, Qt::AscendingOrder);
    else
        model_->sort(0, Qt::DescendingOrder);
}


void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QString str1 = QString::asprintf("模型索引：row=%d, col=%d ", index.row(), index.column());
    QVariant data = model_->data(index);
    QString str2 = data.toString();
    ui->statusbar->showMessage(str1 + str2);
}


void MainWindow::on_btnClearTex_clicked()
{
    ui->plainTextEdit->clear();
}


void MainWindow::on_btnShow_clicked()
{
    QStringList str_list = model_->stringList();
    ui->plainTextEdit->clear();
    for (int i = 0; i < str_list.size(); i++)
        ui->plainTextEdit->appendPlainText(str_list.at(i));
}


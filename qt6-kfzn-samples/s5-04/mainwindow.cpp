#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->splitter_2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    model_ = new QFileSystemModel(this);
    model_->setRootPath(QDir::currentPath());
    ui->treeView->setModel(model_);
    ui->listView->setModel(model_);
    ui->tableView->setModel(model_);

    // 点击treeview节点时，设置listview和tableview根节点为点击的节点
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), ui->listView, SLOT(setRootIndex(QModelIndex)));
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), ui->tableView, SLOT(setRootIndex(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    ui->labFileName->setText(model_->fileName(index));
    int sz = model_->size(index) / 1024;
    if (sz < 1024)
        ui->labFileSize->setText(QString("%1 KB").arg(sz));
    else
        ui->labFileSize->setText(QString::asprintf("%.1f MB", sz/1024.0));
    ui->labNodeType->setText(model_->type(index));
    ui->chkIsDir->setChecked(model_->isDir(index));
    ui->labPath->setText(model_->filePath(index));
}


void MainWindow::on_actSetRootDir_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, "选择目录", QDir::currentPath());
    if (!dir.isEmpty()) {
        model_->setRootPath(dir);
        ui->treeView->setRootIndex(model_->index(dir));
    }
}


void MainWindow::on_rbtnShowDirFile_clicked()
{
    ui->gourpFilter->setEnabled(true);
    model_->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
}


void MainWindow::on_rbtnShowDir_clicked()
{
    ui->gourpFilter->setEnabled(false);
    model_->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
}


void MainWindow::on_chkFileFilter_clicked(bool checked)
{
    model_->setNameFilterDisables(!checked);
    ui->comboFilter->setEnabled(checked);
    ui->btnApplyFilter->setEnabled(checked);
}


void MainWindow::on_btnApplyFilter_clicked()
{
    QString flts = ui->comboFilter->currentText().trimmed();
    QStringList filter = flts.split(";", Qt::SkipEmptyParts);
    model_->setNameFilters(filter);
}


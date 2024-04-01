#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model_ = new QStandardItemModel(6, 4, this);

    QStringList headers;
    headers << "姓名" << "性别" << "学位" << "部门";
    model_->setHorizontalHeaderLabels(headers);
    selection_ = new QItemSelectionModel(model_);
    connect(selection_, &QItemSelectionModel::currentChanged, this, &MainWindow::do_model_currentChanged);

    ui->tableView->setModel(model_);
    ui->tableView->setSelectionModel(selection_);
    setCentralWidget(ui->tableView);

    // 创建状态栏
    lab_cell_pos_ = new QLabel("当前单元格：", this);
    lab_cell_pos_->setMinimumWidth(180);
    lab_cell_pos_->setAlignment(Qt::AlignCenter);
    ui->statusbar->addWidget(lab_cell_pos_);

    lab_cell_txt_ = new QLabel("单元格内容：", this);
    lab_cell_txt_->setMinimumWidth(200);
    ui->statusbar->addWidget(lab_cell_txt_);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_model_currentChanged(const QModelIndex &current, const QModelIndex &previous) {
    Q_UNUSED(previous);
    if (current.isValid()) {
        lab_cell_pos_->setText(QString::asprintf("当前单元格: %d行，%d列", current.row(), current.column()));
        QStandardItem *it;
        it = model_->itemFromIndex(current);
        this->lab_cell_txt_->setText("单元格内容：" + it->text());
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton result;
    result = QMessageBox::question(this, "确认", "确定要退出本程序吗？");
    if (result == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}


void MainWindow::on_actSetRC_triggered()
{
    DialogSize *dialogsize = new DialogSize(this);
    dialogsize->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    dialogsize->setRowColumn(model_->rowCount(), model_->columnCount());
    int ret = dialogsize->exec();
    if (ret == QDialog::Accepted) {
        model_->setColumnCount(dialogsize->columnCount());
        model_->setRowCount(dialogsize->rowCount());
    }
    delete dialogsize;
}


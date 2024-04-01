#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QCloseEvent>

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

void MainWindow::do_setCellText(int row, int col, QString &text) {
    QModelIndex index = model_->index(row, col);
    selection_->clearSelection();
    selection_->setCurrentIndex(index, QItemSelectionModel::Select);
    model_->setData(index, text, Qt::DisplayRole);
}


void MainWindow::on_actSetHeader_triggered()
{
    if (dlg_set_headers == nullptr)
        dlg_set_headers = new DialogHeaders(this);

    if (dlg_set_headers->headerList().size() != model_->columnCount()) {
        QStringList hdrs;
        for (int i = 0; i < model_->columnCount(); i++)
            hdrs.append(model_->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
        dlg_set_headers->setHeaderList(hdrs);
    }

    int ret = dlg_set_headers->exec();
    if (ret == QDialog::Accepted) {
        QStringList hdrs = dlg_set_headers->headerList();
        model_->setHorizontalHeaderLabels(hdrs);
    }

    // delete dlg_set_headers; // 不删除对象，生命周期和MainWindow一样
}


void MainWindow::on_actCell_triggered()
{
    DialogLocate *dlg_locate = new DialogLocate(this);
    dlg_locate->setAttribute(Qt::WA_DeleteOnClose, true);       // 关闭dialog自动删除对象
    dlg_locate->setWindowFlag(Qt::WindowStaysOnTopHint);
    dlg_locate->setSpinRange(model_->rowCount(), model_->columnCount());

    // spinbox显示一开始的row, col
    QModelIndex index = selection_->currentIndex();
    if (index.isValid())
        dlg_locate->setSpinValue(index.row(), index.column());

    // dlg_locate修改celltext信号 --- mainwindow::设置celltext
    connect(dlg_locate, &DialogLocate::changeCellText, this, &MainWindow::do_setCellText);

    connect(dlg_locate, &DialogLocate::changeActionEnable, ui->actCell, &QAction::setEnabled);

    // 点击tableview的cell， dlg_locate显示被点击的坐标
    connect(this, &MainWindow::cellIndexChanged, dlg_locate, &DialogLocate::setSpinValue);

    dlg_locate->setModal(false);
    dlg_locate->show();      // 以非模态方式显示对话框
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    emit cellIndexChanged(index.row(), index.column());
}


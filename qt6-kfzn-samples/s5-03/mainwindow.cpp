#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFileDialog>
#include <QCoreApplication>


void MainWindow::initModelData(QStringList &content){
    int row_cnt = content.size();
    model_->setRowCount(row_cnt - 1);       // first line is header
    QStringList header = content.at(0).split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    model_->setHorizontalHeaderLabels(header);

    QStandardItem *it;
    for (int i = 1; i < row_cnt; i++) {
        QString line = content.at(i);
        QStringList line_contents = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

        int j;
        for (j = 0; j < FixColumnCount - 1; j++) {
            it = new QStandardItem(line_contents.at(j));
            model_->setItem(i - 1, j, it);
        }

        it = new QStandardItem(line_contents.at(j));
        it->setCheckable(true);
        it->setBackground(Qt::yellow);
        if (line_contents.at(j) == "0")
            it->setCheckState(Qt::Unchecked);
        else
            it->setCheckState(Qt::Checked);
        model_->setItem(i - 1, j, it);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model_ = new QStandardItemModel(2, FixColumnCount, this);
    selection_ = new QItemSelectionModel(model_, this);
    connect(selection_, &QItemSelectionModel::currentChanged, this, &MainWindow::do_currentChanged);
    setCentralWidget(ui->splitter);

    // 为tableView设置数据模型、数据选择模型
    ui->tableView->setModel(model_);
    ui->tableView->setSelectionModel(selection_);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);

    // 设置代理编辑器
    int_spin_delegate_ = new IntSpinDelegate(this);
    ui->tableView->setItemDelegateForColumn(0, int_spin_delegate_);

    float_spin_delegate_= new FloatSpinDelegate(this);
    ui->tableView->setItemDelegateForColumn(1, float_spin_delegate_);
    ui->tableView->setItemDelegateForColumn(2, float_spin_delegate_);
    ui->tableView->setItemDelegateForColumn(3, float_spin_delegate_);

    combo_box_delegate_ = new ComboBoxDelegate(this);
    QStringList items;
    items << "优" << "良" << "一般" << "不及格";
    combo_box_delegate_->setItems(items, false);
    ui->tableView->setItemDelegateForColumn(4, combo_box_delegate_);

    // 设置状态栏
    lab_cur_file_ = new QLabel("当前文件：", this);
    lab_cur_file_->setMinimumWidth(200);
    lab_cell_pos_ = new QLabel("当前单元格：", this);
    lab_cell_pos_->setMinimumWidth(180);
    lab_cell_pos_->setAlignment(Qt::AlignCenter);
    lab_cell_text_ = new QLabel("单元格内容：", this);
    lab_cell_text_->setMinimumWidth(150);

    ui->statusbar->addWidget(lab_cur_file_);
    ui->statusbar->addWidget(lab_cell_pos_);
    ui->statusbar->addWidget(lab_cell_text_);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::do_currentChanged(const QModelIndex &current, const QModelIndex &previous){
    Q_UNUSED(previous);

    if (current.isValid()) {
        lab_cell_pos_->setText(QString("当前单元格：%1行 %2列").arg(current.row()).arg(current.column()));
        QStandardItem *it = model_->itemFromIndex(current);
        lab_cell_text_->setText("单元格内容：" + it->text());
    }
}

void MainWindow::on_actOpen_triggered()
{
    QString cur_path = QCoreApplication::applicationDirPath();
    QString filename = QFileDialog::getOpenFileName(this, "打开一个文件", cur_path, "数据文件(*.txt);;所有文件(*.*)");

    if (filename.isEmpty())
        return;

    QStringList file_content;
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        ui->plainTextEdit->clear();

        while (!stream.atEnd()) {
            QString line = stream.readLine();
            ui->plainTextEdit->appendPlainText(line);
            file_content.append(line);
        }
        file.close();

        lab_cur_file_->setText("当前文件：" + filename);
        ui->actAppend->setEnabled(true);
        ui->actInsert->setEnabled(true);
        ui->actDel->setEnabled(true);

        initModelData(file_content);
    }
}


void MainWindow::on_actAppend_triggered()
{
    QList<QStandardItem*> item_list;
    QStandardItem *it;
    for (int i = 0; i < FixColumnCount - 1; i++){
        it = new QStandardItem("0");
        item_list.append(it);
    }

    QString str = model_->headerData(model_->columnCount()-1, Qt::Horizontal, \
                                     Qt::DisplayRole).toString();
    it = new QStandardItem(str);
    it->setCheckable(true);
    it->setCheckState(Qt::Unchecked);
    item_list.append(it);

    // append
    model_->insertRow(model_->rowCount(), item_list);
    QModelIndex cur_index = model_->index(model_->rowCount() - 1, 0);
    selection_->clearSelection();
    selection_->setCurrentIndex(cur_index, QItemSelectionModel::Select);
}


void MainWindow::on_actInsert_triggered()
{
    QList<QStandardItem*> item_list;
    QStandardItem *it;
    for (int i = 0; i < FixColumnCount - 1; i++){
        it = new QStandardItem("0");
        item_list.append(it);
    }

    QString str = model_->headerData(model_->columnCount()-1, Qt::Horizontal, \
                                     Qt::DisplayRole).toString();
    it = new QStandardItem(str);
    it->setCheckable(true);
    it->setCheckState(Qt::Unchecked);
    item_list.append(it);

    // insert
    QModelIndex cur_index = selection_->currentIndex();
    model_->insertRow(cur_index.row(), item_list);
    selection_->clearSelection();
    selection_->setCurrentIndex(cur_index, QItemSelectionModel::Select);
}


void MainWindow::on_actDel_triggered()
{
    QModelIndex cur_index = selection_->currentIndex();
    if (cur_index.row() == model_->rowCount() - 1)
        model_->removeRow(cur_index.row());
    else {
        model_->removeRow(cur_index.row());
        selection_->setCurrentIndex(cur_index, QItemSelectionModel::Select);
    }
}


void MainWindow::on_actLeft_triggered()
{
    if (!selection_->hasSelection())
        return;

    QModelIndexList indexes = selection_->selectedIndexes();
    for (int i = 0; i < indexes.count(); i++) {
        QModelIndex idx = indexes.at(i);
        QStandardItem *it = model_->itemFromIndex(idx);
        it->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    }
}


void MainWindow::on_actMiddle_triggered()
{
    if (!selection_->hasSelection())
        return;

    QModelIndexList indexes = selection_->selectedIndexes();
    for (int i = 0; i < indexes.count(); i++) {
        QModelIndex idx = indexes.at(i);
        QStandardItem *it = model_->itemFromIndex(idx);
        it->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    }
}


void MainWindow::on_actRight_triggered()
{
    if (!selection_->hasSelection())
        return;

    QModelIndexList indexes = selection_->selectedIndexes();
    for (int i = 0; i < indexes.count(); i++) {
        QModelIndex idx = indexes.at(i);
        QStandardItem *it = model_->itemFromIndex(idx);
        it->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }
}


void MainWindow::on_actBold_triggered()
{

}


void MainWindow::on_actBold_triggered(bool checked)
{
    if (!selection_->hasSelection())
        return;

    QModelIndexList indexes = selection_->selectedIndexes();
    for (int i = 0; i < indexes.count(); i++) {
        QModelIndex idx = indexes.at(i);
        QStandardItem *it = model_->itemFromIndex(idx);
        QFont font = it->font();
        font.setBold(checked);
        it->setFont(font);
    }
}


void MainWindow::on_actModelData_toggled(bool arg1)
{

}


void MainWindow::on_actModelData_triggered()
{
    ui->plainTextEdit->clear();
    QString str;
    QStandardItem *it;

    // header
    for (int i = 0; i < model_->columnCount(); i++) {
        it = model_->horizontalHeaderItem(i);
        str += it->text() + "\t";
    }
    ui->plainTextEdit->appendPlainText(str);

    // contents
    for (int i = 0; i < model_->rowCount(); i++) {
        str = "";
        for (int j = 0; j < model_->columnCount() - 1; j++) {
            it = model_->item(i, j);
            str += it->text() + "\t";
        }
        it = model_->item(i, model_->columnCount() - 1);
        str += (it->checkState() == Qt::Checked) ? "1" : "0";
        ui->plainTextEdit->appendPlainText(str);
    }
}


#include "formtable.h"
#include "ui_formtable.h"

#include "dialogsize.h"

FormTable::FormTable(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FormTable)
{
    ui->setupUi(this);
    model_ = new QStandardItemModel(12,6,this);
    selection_ = new QItemSelectionModel(model_, this);
    ui->tableView->setModel(model_);
    ui->tableView->setSelectionModel(selection_);
}

FormTable::~FormTable()
{
    delete ui;
}

void FormTable::on_actSetTabSize_triggered()
{

    DialogSize *dlg_size = new DialogSize(this);
    dlg_size->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    dlg_size->setRowColumn(model_->rowCount(), model_->columnCount());
    int ret = dlg_size->exec();
    if (ret == QDialog::Accepted) {
        model_->setRowCount(dlg_size->rowCount());
        model_->setColumnCount(dlg_size->columnCount());
    }
    delete dlg_size;
}


void FormTable::on_actSetHeaders_triggered()
{
    if (dlg_set_headers_ == nullptr)
        dlg_set_headers_ = new DialogHeaders(this);

    if (dlg_set_headers_->headerList().count() != model_->columnCount()) {
        QStringList hdrs;
        for (int i = 0; i < model_->columnCount(); i++) {
            hdrs.append(model_->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
        }
        dlg_set_headers_->setHeaderList(hdrs);
    }
    int ret = dlg_set_headers_->exec();
    if (ret == QDialog::Accepted) {
        QStringList hdrs = dlg_set_headers_->headerList();
        model_->setHorizontalHeaderLabels(hdrs);
    }
}


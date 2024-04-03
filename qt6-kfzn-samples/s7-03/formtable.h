#ifndef FORMTABLE_H
#define FORMTABLE_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>

#include "dialogheaders.h"

namespace Ui {
class FormTable;
}

class FormTable : public QMainWindow
{
    Q_OBJECT
private:
    DialogHeaders *dlg_set_headers_ = nullptr;
    QStandardItemModel *model_;
    QItemSelectionModel *selection_;

public:
    explicit FormTable(QWidget *parent = nullptr);
    ~FormTable();

private slots:
    void on_actSetTabSize_triggered();

    void on_actSetHeaders_triggered();

private:
    Ui::FormTable *ui;
};

#endif // FORMTABLE_H

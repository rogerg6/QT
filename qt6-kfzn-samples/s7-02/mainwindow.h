#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include "DialogHeaders"
#include "dialogsize.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLabel *lab_cell_pos_;
    QLabel *lab_cell_txt_;
    QStandardItemModel *model_;
    QItemSelectionModel *selection_;
    DialogHeaders *dlg_set_headers = nullptr;

protected:
    void closeEvent(QCloseEvent *event);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void do_model_currentChanged(const QModelIndex &current, const QModelIndex &previous);

    void on_actSetRC_triggered();

public slots:
    void do_setCellText(int row, int col, QString &text);
signals:
    void cellIndexChanged(int row_no, int col_no);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

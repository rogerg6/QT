#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QStringList>

#define FixColumnCount 6

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLabel *lab_cur_file_;
    QLabel *lab_cell_pos_;
    QLabel *lab_cell_text_;

    QStandardItemModel *model_;
    QItemSelectionModel *selection_;

    void initModelData(QStringList &content);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void do_currentChanged(const QModelIndex &current, const QModelIndex &previous);

    void on_actOpen_triggered();

    void on_actAppend_triggered();

    void on_actInsert_triggered();

    void on_actDel_triggered();

    void on_actLeft_triggered();

    void on_actMiddle_triggered();

    void on_actRight_triggered();

    void on_actBold_triggered();

    void on_actBold_triggered(bool checked);

    void on_actModelData_toggled(bool arg1);

    void on_actModelData_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

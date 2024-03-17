#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QStringListModel>



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QStringList str_list_;
    QStringListModel *model_;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_chkEditable_clicked(bool checked);

    void on_btnRestoreList_clicked();

    void on_btnClearList_clicked();

    void on_btnAddItem_clicked();

    void on_btnInsertItem_clicked();

    void on_btnDelItem_clicked();

    void on_btnMoveUp_clicked();

    void on_btnMoveDown_clicked();

    void on_btnSort_clicked(bool checked);

    void on_listView_clicked(const QModelIndex &index);

    void on_btnClearTex_clicked();

    void on_btnShow_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

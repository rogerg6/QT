#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QFileSystemModel *model_;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_actSetRootDir_triggered();

    void on_rbtnShowDirFile_clicked();

    void on_rbtnShowDir_clicked();

    void on_chkFileFilter_clicked(bool checked);

    void on_btnApplyFilter_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

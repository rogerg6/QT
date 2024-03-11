#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setActionForButton();
    void createSelectionMenu();

private slots:
    void on_actListInit_triggered();

    void on_chkListEditable_clicked(bool checked);

    void on_actListClear_triggered();

    void on_actListInsert_triggered();

    void on_actListAppend_triggered();

    void on_actListDelete_triggered();

    void on_actSelPopMenu_triggered();

    void on_actSelAll_triggered();

    void on_actSelNone_triggered();

    void on_actSelInvs_triggered();

    void on_chkEnableSort_clicked(bool checked);

    void on_btnAscOrder_clicked();

    void on_btnDesOrder_clicked();

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_listWidget_currentRowChanged(int currentRow);

    void on_btnTextClear_clicked();

    void on_btnTextNewLine_clicked();

    void on_listWidget_currentTextChanged(const QString &currentText);

    void on_listWidget_itemActivated(QListWidgetItem *item);

    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_itemEntered(QListWidgetItem *item);

    void on_listWidget_itemPressed(QListWidgetItem *item);

    void on_listWidget_itemSelectionChanged();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

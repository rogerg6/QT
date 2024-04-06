#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <formdoc.h>

#include <QMdiSubWindow>

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

private slots:
    void on_actNew_triggered();

    void on_actOpen_triggered();



    void on_actCloseAll_triggered();

    void on_actCascade_triggered();

    void on_actTile_triggered();



    void on_actMDI_triggered(bool checked);

    void on_actSave_triggered();

    void on_actCut_triggered();

    void on_actCopy_triggered();

    void on_actPaste_triggered();

    void on_actFont_triggered();

    void on_mdiArea_subWindowActivated(QMdiSubWindow *arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

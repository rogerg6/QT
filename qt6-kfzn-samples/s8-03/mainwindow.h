#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QString filename_;      // 用于测试的文件
    template<class T> void writeByStream(T value);
    template<class T> void readByStream(T &value);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnTestFile_clicked();

    void on_btnInt8Write_clicked();

    void on_btnUint8Write_clicked();

    void on_btnInt16Write_clicked();

    void on_btnUint16Write_clicked();

    void on_btnInt32Write_clicked();

    void on_btnInt64Write_clicked();

    void on_btnBoolWrite_clicked();

    void on_btnFloat16Write_clicked();

    void on_btnFloatWrite_clicked();

    void on_btnDoubleWrite_clicked();

    void on_btnStrWrite_clicked();

    void on_btnQStrWrite_clicked();

    void on_btnFontWrite_clicked();

    void on_btnColorWrite_clicked();

    void on_btnFontIn_clicked();

    void on_btnColorIn_clicked();

    void on_btnInt8Read_clicked();

    void on_btnUint8Read_clicked();

    void on_btnInt16Read_clicked();

    void on_btnUint16Read_clicked();

    void on_btnInt32Read_clicked();

    void on_btnInt64Read_clicked();

    void on_btnBoolRead_clicked();

    void on_btnFloat16Read_clicked();

    void on_btnFloatRead_clicked();

    void on_btnDoubleRead_clicked();

    void on_btnStrRead_clicked();

    void on_btnQStrRead_clicked();

    void on_btnFontRead_clicked();

    void on_btnColorRead_clicked();

    void on_actionEditClear_triggered();

    void on_actionWriteCon_triggered();

    void on_actionReadCon_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

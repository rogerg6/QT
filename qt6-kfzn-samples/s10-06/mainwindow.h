#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPrinter>
#include <QImage>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QString filename_;      // 当前图片名称
    QImage img_;            // 当前图像
    void showImageFeatures(bool formatChanged=true);    // 显示图像属性
    void imageModified(bool modified=true);         // 图像被修改了，改变Action状态
    void printImage(QPainter *painter, QPrinter *printer);          // 打印图片
    void printRGB565Data(QPainter *painter, QPrinter *printer);     // 打印RGB565数据

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void do_paintRequestedImage(QPrinter *printer);     // 用于打印图片
    void do_paintRequestedText(QPrinter *printer);      // 用于打印文本

    void on_actFileOpen_triggered();

    void on_actFileSave_triggered();

    void on_actFileSaveAs_triggered();

    void on_actFileReload_triggered();

    void on_btnImgFormatConvert_clicked();

    void on_actImgZoomIn_triggered();

    void on_actImgZoomOut_triggered();

    void on_actImgRotateLeft_triggered();

    void on_actImgRotateRight_triggered();

    void on_actImgFlipUD_triggered();

    void on_actImgFlipLR_triggered();

    void on_btnGetRGB565_clicked();

    void on_btnSaveAsDataFile_clicked();

    void on_actFilePreview_triggered();

    void on_actFilePrint_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

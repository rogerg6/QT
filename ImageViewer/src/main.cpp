#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("ImageViewer");  // 设置主窗口标题

    // 设置窗口图标
    QIcon icon("C:\\Users\\PC\\Pictures\\zoom.png");
    w.setWindowIcon(icon);

    w.show();
    return a.exec();

}

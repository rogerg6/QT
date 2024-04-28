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
    bool openByIO_Whole(const QString &filename);
    bool openByIO_Lines(const QString &filename);
    bool saveByIO_Whole(const QString &filename);
    bool saveByIO_Safe(const QString &filename);

    bool openByStream_Whole(const QString &filename);
    bool openByStream_Lines(const QString &filename);
    bool saveByStream_Whole(const QString &filename);
    bool saveByStream_Safe(const QString &filename);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionQFileOpen_triggered();

    void on_actionQFileSaveAs_triggered();

    void on_actionQSaveFileSaveAs_triggered();

    void on_actionQTextStreamOpen_triggered();

    void on_actionQTextStreamSaveAs_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

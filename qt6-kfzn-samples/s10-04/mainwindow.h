#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <QResizeEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QGraphicsScene *scene_;
    QLabel *lab_view_cord_;
    QLabel *lab_scene_cord_;
    QLabel *lab_item_cord_;
    void iniGraphicsSystem();

protected:
    void resizeEvent(QResizeEvent *event);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void do_mouseMovePoint(QPoint point);
    void do_mouseClicked(QPoint point);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

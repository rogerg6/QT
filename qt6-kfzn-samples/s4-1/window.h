#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

private slots:
    void on_btnCharJudge_clicked();

    void on_btnGetChars_clicked();

    void on_btnClear_clicked();

private:
    Ui::Widget *ui;
};
#endif // WINDOW_H

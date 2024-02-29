#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Window;
}
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

private slots:
    void do_setFontColor();
    void on_chkBoxUnderline_clicked(bool checked);

    void on_chkBoxItalic_clicked(bool checked);

    void on_chkBoxBold_clicked(bool checked);


    void on_btnClear_clicked();

private:
    Ui::Window *ui;
};
#endif // WINDOW_H

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "tperson.h"


namespace Ui {
class Widget;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

private slots:
    void do_ageChanged(int value);
    void do_spinChanged(int value);

    void on_btnBoyInc_clicked();
    void on_btnGirlInc_clicked();

    void on_btnClear_clicked();

    void on_btnClassInfo_clicked();

private:
    TPerson *boy, *girl;

    Ui::Widget *ui;
};
#endif // WINDOW_H

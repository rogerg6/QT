#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event);

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

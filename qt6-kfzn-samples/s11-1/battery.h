#ifndef BATTERY_H
#define BATTERY_H

#include <QWidget>
#include <QSize>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Battery : public QWidget
{
    Q_OBJECT

    // 自定义属性
    Q_PROPERTY(int power_level_ READ powerLevel WRITE setPowerLevel NOTIFY powerLevelChanged)
    Q_PROPERTY(int warn_level_ READ warnLevel WRITE setWarnLevel)


protected:
    void paintEvent(QPaintEvent *event);         // 绘制组件并显示效果
public:
    explicit Battery(QWidget *parent = nullptr);


    void setPowerLevel(int pow);
    int powerLevel();
    void setWarnLevel(int warn);
    int warnLevel();
    QSize sizeHint();

signals:
    void powerLevelChanged(int pow);


private:
    Ui::Widget *ui;

    QColor back_clr = Qt::white;      // 背景色
    QColor border_clr = Qt::black;    // 电池边框颜色
    QColor power_clr = Qt::green;     // 电量柱颜色
    QColor warn_clr = Qt::red;        // 电量短缺时的颜色

    int power_level_ = 50;   // 电量值0~100
    int warn_level_ = 20;    // 电量低阈值
};
#endif // BATTERY_H

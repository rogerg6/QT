#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAbstractItemView>
#include <QGroupBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

private:
    int getDropActionIndex(Qt::DropAction action_type);
    Qt::DropAction getDropActionType(int index);
    void refreshToUI(QGroupBox *cur_groupbox);

    QAbstractItemView *item_view_ = nullptr;

protected:
    bool eventFilter(QObject *watched, QEvent *event);

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_rbtnListSrc_clicked();

    void on_rbtnListWidget_clicked();

    void on_rbtntreeWidget_clicked();

    void on_rbtnTableWidget_clicked();

    void on_chkAcceptDrops_clicked(bool checked);

    void on_chkDragEnable_clicked(bool checked);

    void on_comboMode_currentIndexChanged(int index);

    void on_comboAction_currentIndexChanged(int index);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

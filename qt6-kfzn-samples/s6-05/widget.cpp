#include "widget.h"
#include "ui_widget.h"

#include <QMessageBox>
#include <QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 安装事件过滤器
    ui->listSrc->installEventFilter(this);
    ui->listWidget->installEventFilter(this);
    ui->treeWidget->installEventFilter(this);
    ui->tableWidget->installEventFilter(this);

    // 设置4个项数据的拖放操作相关属性
    ui->listSrc->setAcceptDrops(true);
    ui->listSrc->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listSrc->setDragEnabled(true);
    ui->listSrc->setDefaultDropAction(Qt::CopyAction);

    ui->listWidget->setAcceptDrops(true);
    ui->listWidget->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listWidget->setDragEnabled(true);
    ui->listWidget->setDefaultDropAction(Qt::CopyAction);

    ui->treeWidget->setAcceptDrops(true);
    ui->treeWidget->setDragDropMode(QAbstractItemView::DragDrop);
    ui->treeWidget->setDragEnabled(true);
    ui->treeWidget->setDefaultDropAction(Qt::CopyAction);

    ui->tableWidget->setAcceptDrops(true);
    ui->tableWidget->setDragDropMode(QAbstractItemView::DragDrop);
    ui->tableWidget->setDragEnabled(true);
    ui->tableWidget->setDefaultDropAction(Qt::MoveAction);
}

Widget::~Widget()
{
    delete ui;
}

int Widget::getDropActionIndex(Qt::DropAction action_type){
    switch(action_type) {
    case Qt::CopyAction:
        return 0;
    case Qt::MoveAction:
        return 1;
    case Qt::LinkAction:
        return 2;
    case Qt::IgnoreAction:
        return 3;
    default:
        return 0;
    }
}


Qt::DropAction Widget::getDropActionType(int index){
    switch(index) {
    case 0:
        return Qt::CopyAction;
    case 1:
        return Qt::MoveAction;
    case 2:
        return Qt::LinkAction;
    case 3:
        return Qt::IgnoreAction;
    default:
        return Qt::CopyAction;
    }
}


void Widget::refreshToUI(QGroupBox *cur_groupbox){
    ui->chkAcceptDrops->setChecked(item_view_->acceptDrops());
    ui->chkDragEnable->setChecked(item_view_->dragEnabled());
    ui->comboMode->setCurrentIndex((int)item_view_->dragDropMode());
    int index = getDropActionIndex(item_view_->defaultDropAction());
    ui->comboAction->setCurrentIndex(index);

    QFont font = ui->groupBox_3->font();
    font.setBold(false);
    ui->groupBox_3->setFont(font);
    ui->groupBox_4->setFont(font);
    ui->groupBox_5->setFont(font);
    ui->groupBox_6->setFont(font);
    font.setBold(true);
    // 当前view字体设置为bold
    cur_groupbox->setFont(font);
}

bool Widget::eventFilter(QObject *watched, QEvent *event){
    if (event->type() != QEvent::KeyPress)
        return QWidget::eventFilter(watched, event);

    QKeyEvent *keyev = static_cast<QKeyEvent*>(event);
    if (keyev->key() != Qt::Key_Delete)
        return QWidget::eventFilter(watched, event);

    if (watched == ui->listSrc) {
        QListWidgetItem *it = ui->listSrc->takeItem(ui->listSrc->currentRow());
        delete it;
    } else if (watched == ui->listWidget) {
        QListWidgetItem *it = ui->listWidget->takeItem(ui->listWidget->currentRow());
        delete it;
    } else if (watched == ui->treeWidget) {
        QTreeWidgetItem *it = ui->treeWidget->currentItem();
        if (it->parent() != nullptr) {
            QTreeWidgetItem *parit = it->parent();
            parit->removeChild(it);
        } else {
            int index = ui->treeWidget->indexOfTopLevelItem(it);
            ui->treeWidget->takeTopLevelItem(index);
        }
        delete it;
    }   else if (watched == ui->tableWidget) {
        QTableWidgetItem *it = ui->tableWidget->takeItem(ui->tableWidget->currentRow(),
                           ui->tableWidget->currentColumn());
        delete it;
    }

    return true;
}

void Widget::on_rbtnListSrc_clicked()
{
    item_view_ = ui->listSrc;
    refreshToUI(ui->groupBox_3);
}


void Widget::on_rbtnListWidget_clicked()
{
    item_view_ = ui->listWidget;
    refreshToUI(ui->groupBox_4);
}


void Widget::on_rbtntreeWidget_clicked()
{
    item_view_ = ui->treeWidget;
    refreshToUI(ui->groupBox_5);
}


void Widget::on_rbtnTableWidget_clicked()
{
    item_view_ = ui->tableWidget;
    refreshToUI(ui->groupBox_6);
}


void Widget::on_chkAcceptDrops_clicked(bool checked)
{
    item_view_->setAcceptDrops(checked);
}


void Widget::on_chkDragEnable_clicked(bool checked)
{
    item_view_->setDragEnabled(checked);
}


void Widget::on_comboMode_currentIndexChanged(int index)
{
    QAbstractItemView::DragDropMode mode = (QAbstractItemView::DragDropMode)index;
    item_view_->setDragDropMode(mode);
}


void Widget::on_comboAction_currentIndexChanged(int index)
{
    Qt::DropAction action_type = getDropActionType(index);
    item_view_->setDefaultDropAction(action_type);
}


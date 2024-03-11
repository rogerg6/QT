#include "mainwindow.h"
#include "ui_mainwindow.h"

//为QToolButton按钮设置Action
void MainWindow::setActionForButton(){
    ui->btnListInit->setDefaultAction(ui->actListInit);
    ui->btnListClear->setDefaultAction(ui->actListClear);
    ui->btnListInsert->setDefaultAction(ui->actListInsert);
    ui->btnListAppend->setDefaultAction(ui->actListAppend);
    ui->btnListDelete->setDefaultAction(ui->actListDelete);

    ui->tbtnSelAll->setDefaultAction(ui->actSelAll);
    ui->tbtnSelNone->setDefaultAction(ui->actSelNone);
    ui->tbtnSelInvs->setDefaultAction(ui->actSelInvs);
}

void MainWindow::createSelectionMenu(){
    // 创建下拉菜单
    QMenu *menu_sel = new QMenu(this);
    menu_sel->addAction(ui->actSelAll);
    menu_sel->addAction(ui->actSelNone);
    menu_sel->addAction(ui->actSelInvs);

    //listWidget上方的项选择按钮
    ui->tbtnItemSel->setPopupMode(QToolButton::MenuButtonPopup);
    ui->tbtnItemSel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->tbtnItemSel->setDefaultAction(ui->actSelPopMenu);
    ui->tbtnItemSel->setMenu(menu_sel);

    // 工具栏的下拉菜单
    QToolButton * btn = new QToolButton(this);
    btn->setPopupMode(QToolButton::MenuButtonPopup);
    btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    btn->setDefaultAction(ui->actSelPopMenu);
    btn->setMenu(menu_sel);
    ui->toolBar->addWidget(btn);

    // 工具栏退出按钮
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actQuit);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->splitter); //设置中心组件

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    setActionForButton();
    createSelectionMenu();

}

MainWindow::~MainWindow()
{
    delete ui;
}

// 初始化列表
void MainWindow::on_actListInit_triggered()
{
    QListWidgetItem *it;

    QIcon icon;
    icon.addFile(":/images/icons/check2.ico");
    bool chk = ui->chkListEditable->isChecked();

    ui->listWidget->clear();
    for (int i = 0; i < 10; i++) {
        QString str = QString("Item %1").arg(i);
        it = new QListWidgetItem();

        it->setText(str);
        it->setIcon(icon);
        it->setCheckState(Qt::Checked);
        if (chk)
            it->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
        else
            it->setFlags(Qt::ItemIsSelectable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
        ui->listWidget->addItem(it);
    }
}

// 清空列表
void MainWindow::on_actListClear_triggered()
{
    ui->listWidget->clear();
}

void MainWindow::on_chkListEditable_clicked(bool checked)
{
    int cnt;
    QListWidgetItem *it;

    cnt = ui->listWidget->count();
    for (int i = 0; i < cnt; ++i){
        it = ui->listWidget->item(i);
        if (checked)
            it->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
        else
            it->setFlags(Qt::ItemIsSelectable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
    }
}

// 插入项
void MainWindow::on_actListInsert_triggered()
{
    QIcon icon(":/images/icons/check2.ico");
    bool chk = ui->chkListEditable->isChecked();

    QListWidgetItem *it = new QListWidgetItem("Inerted item");
    it->setIcon(icon);
    it->setCheckState(Qt::Checked);

    if (chk)
        it->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
    else
        it->setFlags(Qt::ItemIsSelectable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);

    ui->listWidget->insertItem(ui->listWidget->currentRow(), it);
}

// 在末尾添加项
void MainWindow::on_actListAppend_triggered()
{
    QIcon icon(":/images/icons/check2.ico");
    bool chk = ui->chkListEditable->isChecked();

    QListWidgetItem *it = new QListWidgetItem("Added item");
    it->setIcon(icon);
    it->setCheckState(Qt::Checked);

    if (chk)
        it->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
    else
        it->setFlags(Qt::ItemIsSelectable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);

    ui->listWidget->addItem(it);
}

// 删除项
void MainWindow::on_actListDelete_triggered()
{
    int row = ui->listWidget->currentRow();

    QListWidgetItem *it = ui->listWidget->takeItem(row);
    delete it;   // 需要手动删除
}

// 项选择
void MainWindow::on_actSelPopMenu_triggered()
{

}

// 全选
void MainWindow::on_actSelAll_triggered()
{
    int cnt = ui->listWidget->count();
    for (int i = 0; i <cnt; i++){
        QListWidgetItem *it = ui->listWidget->item(i);
        it->setCheckState(Qt::Checked);
    }
}

// 空选
void MainWindow::on_actSelNone_triggered()
{
    int cnt = ui->listWidget->count();
    for (int i = 0; i <cnt; i++){
        QListWidgetItem *it = ui->listWidget->item(i);
        it->setCheckState(Qt::Unchecked);
    }
}

// 反选
void MainWindow::on_actSelInvs_triggered()
{
    int cnt = ui->listWidget->count();
    for (int i = 0; i <cnt; i++){
        QListWidgetItem *it = ui->listWidget->item(i);
        if (it->checkState() == Qt::Checked)
            it->setCheckState(Qt::Unchecked);
        else
            it->setCheckState(Qt::Checked);
    }
}


void MainWindow::on_chkEnableSort_clicked(bool checked)
{
    ui->listWidget->setSortingEnabled(checked);
}

// 升序
void MainWindow::on_btnAscOrder_clicked()
{
    if (ui->listWidget->isSortingEnabled())
        ui->listWidget->sortItems(Qt::AscendingOrder);
}

// 降序
void MainWindow::on_btnDesOrder_clicked()
{
    if (ui->listWidget->isSortingEnabled())
        ui->listWidget->sortItems(Qt::DescendingOrder);
}

// 鼠标右键弹出actions
void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu *menu_list = new QMenu(this);
    menu_list->addAction(ui->actListInit);
    menu_list->addAction(ui->actListClear);
    menu_list->addAction(ui->actListInsert);
    menu_list->addAction(ui->actListAppend);
    menu_list->addAction(ui->actListDelete);
    menu_list->addSeparator();
    menu_list->addAction(ui->actSelAll);
    menu_list->addAction(ui->actSelNone);
    menu_list->addAction(ui->actSelInvs);

    menu_list->exec(QCursor::pos());

    delete menu_list;   // 用完需要删除menu list
}


void MainWindow::on_btnTextClear_clicked()
{
    ui->plainTextEdit->clear();
}


void MainWindow::on_btnTextNewLine_clicked()
{
    ui->plainTextEdit->appendPlainText("");
}

// listwidget的各种信号
// current是当前点击的项，previous是上次点击的项
void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QString str;
    if (current != nullptr){
        if (previous == nullptr)
            str = "当前项=" + current->text();
        else
            str = "当前项=" + current->text() + ", 前一项=" + previous->text();
        ui->lineEdit->setText(str);
    }
    ui->plainTextEdit->appendPlainText("currentItemChanged signal sent");
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    ui->plainTextEdit->appendPlainText(QString("currentRowChanged signal sent. 当前行=%1").arg(currentRow));
}

void MainWindow::on_listWidget_currentTextChanged(const QString &currentText)
{
    ui->plainTextEdit->appendPlainText("currentTextChanged()信号被发射，currentText="+currentText);
}


void MainWindow::on_listWidget_itemActivated(QListWidgetItem *item)
{
    ui->plainTextEdit->appendPlainText("itemActivated()信号被发射，"+item->text());
}


void MainWindow::on_listWidget_itemChanged(QListWidgetItem *item)
{
    ui->plainTextEdit->appendPlainText("itemChanged()信号被发射，"+item->text());
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->plainTextEdit->appendPlainText("itemClicked()信号被发射，"+item->text());
}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item);
    ui->plainTextEdit->appendPlainText("itemDoubleClicked()信号被发射，"+item->text());
}


void MainWindow::on_listWidget_itemEntered(QListWidgetItem *item)
{
    ui->plainTextEdit->appendPlainText("itemEntered()信号被发射，"+item->text());
}


void MainWindow::on_listWidget_itemPressed(QListWidgetItem *item)
{
    ui->plainTextEdit->appendPlainText("itemPressed()信号被发射，"+item->text());
}


void MainWindow::on_listWidget_itemSelectionChanged()
{
    ui->plainTextEdit->appendPlainText("itemSelectionChanged()信号被发射");
}


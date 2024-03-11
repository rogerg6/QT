#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

// 构建表头
void MainWindow::buildTreeHeader(){
    ui->treeFile->clear();

    QTreeWidgetItem *header = new QTreeWidgetItem();
    header->setText(colItem, "目录和文件");
    header->setText(colItemType, "节点类型");
    header->setText(colDate, "最后修改日期");

    header->setTextAlignment(colItem, Qt::AlignHCenter | Qt::AlignVCenter);
    header->setTextAlignment(colItemType, Qt::AlignHCenter | Qt::AlignVCenter);

    ui->treeFile->setHeaderItem(header);
}

//初始化目录树，创建一个顶层节点
void MainWindow::initTree(){
    QIcon icon(":/images/icons/icons/15.ico");
    QTreeWidgetItem *it = new QTreeWidgetItem(itTopItem);
    it->setIcon(colItem, icon);
    it->setText(colItem, "图片");
    it->setText(colItemType, "Top Item");
    it->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    it->setCheckState(colItem, Qt::Checked);

    ui->treeFile->addTopLevelItem(it);
}

void     MainWindow::addFolderItem(QTreeWidgetItem *parItem, QString dirName)         {
    QIcon icon(":/images/icons/icons/open3.bmp");
    QString node_text = getFinalFolderName(dirName);
    QTreeWidgetItem *item = new QTreeWidgetItem(itGroupItem);
    item->setIcon(colItem, icon);
    item->setText(colItem, node_text);
    item->setText(colItemType, "Group Item");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    item->setCheckState(colItem, Qt::Checked);
    item->setData(colItem, Qt::UserRole, QVariant(dirName));
    parItem->addChild(item);
}

QString  MainWindow::getFinalFolderName(const QString &fullPathName)                  {
    int cnt = fullPathName.length();
    int i = fullPathName.lastIndexOf("/");
    QString str = fullPathName.right(cnt-i-1);
    return str;
}

void 	 MainWindow::addImageItem(QTreeWidgetItem *parItem, QString aFileName)        {
    QIcon icon(":/images/icons/icons/31.ico");
    QFileInfo fileinfo(aFileName);          // QFileInfo用于获取文件信息
    QString node_text = fileinfo.fileName();
    QDateTime birthDate = fileinfo.lastModified();

    QTreeWidgetItem *item;
    item = new QTreeWidgetItem(itImageItem);
    item->setIcon(colItem, icon);
    item->setText(colItem, node_text);
    item->setText(colItemType, "Image Item");
    item->setText(colDate, birthDate.toString("yyyy-MM-dd"));
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    item->setCheckState(colItem, Qt::Checked);
    item->setData(colItem, Qt::UserRole, QVariant(aFileName));
    parItem->addChild(item);
}

void 	 MainWindow::displayImage(QTreeWidgetItem *item)                              {
    QString filename = item->data(colItem, Qt::UserRole).toString();
    labFileName->setText(filename);
    labNodeText->setText(item->text(colItem));

    pixmap_.load(filename);
    ui->actFitH->trigger();         // 触发trigger信号， 触发槽函数
    ui->actFitH->setEnabled(true);
    ui->actFitW->setEnabled(true);
    ui->actZoomIn->setEnabled(true);
    ui->actZoomOut->setEnabled(true);
    ui->actFitReal->setEnabled(true);
}

// 遍历修改item及其子目录下的文件名
void 	 MainWindow::changeItemCaption(QTreeWidgetItem *item)                         {
    QString str = "*" + item->text(colItem);
    item->setText(colItem, str);
    if (item->childCount() > 0)
        for (int i = 0; i < item->childCount(); i++)
            changeItemCaption(item->child(i));
}

void 	 MainWindow::deleteItem(QTreeWidgetItem *parItem, QTreeWidgetItem *item)      {
    if (item->childCount() > 0) {
        int count = item->childCount();
        QTreeWidgetItem *tmpParItem = item;
        for (int i = 0; i < count; i++)
            deleteItem(tmpParItem, tmpParItem->child(i));
    }
    parItem->removeChild(item);   // 移除节点
    delete item;                  // 从内存中删除对象
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建状态栏上的组件
    labNodeText = new QLabel("节点标题", this);
    labNodeText->setMinimumWidth(200);
    ui->statusbar->addWidget(labNodeText);

    spinRatio = new QSpinBox(this);
    spinRatio->setRange(0,2000);
    spinRatio->setValue(100);
    spinRatio->setSuffix(" %");
    spinRatio->setReadOnly(true);
    spinRatio->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->statusbar->addPermanentWidget(spinRatio);

    labFileName = new QLabel("文件名", this);
    ui->statusbar->addPermanentWidget(labFileName);

    // 初始化目录树
    buildTreeHeader();
    initTree();

    setCentralWidget(ui->scrollArea); //设置中心布局组件
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actAddDir_triggered()
{
    QString dir = QFileDialog::getExistingDirectory();
    if (dir.isEmpty())
        return;
    QTreeWidgetItem *parItem = ui->treeFile->currentItem();
    if (parItem == nullptr)
        return;
    if (parItem->type() != itImageItem)
        addFolderItem(parItem, dir);
}


void MainWindow::on_actAddFile_triggered()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "选择文件","","Images(*.jpg)");

    //一个文件都没选
    if (files.empty())
        return;

    QTreeWidgetItem *parItem, *item;
    item = ui->treeFile->currentItem();
    if (item == nullptr)
        item = ui->treeFile->topLevelItem(0);

    if (item->type() == itImageItem)
        parItem = item->parent();
    else
        parItem = item;

    for (int i = 0; i < files.size(); i++) {
        QString aFileName = files.at(i);
        addImageItem(parItem, aFileName);
    }

    parItem->setExpanded(true);  // 展开父目录
}


void MainWindow::on_treeFile_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous);
    qDebug("currentItemChanged() is emitted.");
    if (current == nullptr)
        return;
    if (current == previous)
        return;

    int var = current->type();
    switch(var) {
    case itTopItem:
        ui->actAddDir->setEnabled(true);
        ui->actAddFile->setEnabled(true);
        ui->actDelNode->setEnabled(false);
        break;
    case itGroupItem:
        ui->actAddDir->setEnabled(true);
        ui->actAddFile->setEnabled(true);
        ui->actDelNode->setEnabled(true);
        break;
    case itImageItem:
        ui->actAddDir->setEnabled(false);
        ui->actAddFile->setEnabled(true);
        ui->actDelNode->setEnabled(true);
        displayImage(current);
    }
}


void MainWindow::on_actDelNode_triggered()
{
    QTreeWidgetItem *it = ui->treeFile->currentItem();
    if (it == nullptr)
        return;
    QTreeWidgetItem *parItem = it->parent();
    deleteItem(parItem, it);
}

// 遍历节点
void MainWindow::on_actScanNode_triggered()
{
    for (int i = 0; i < ui->treeFile->topLevelItemCount(); i++) {
        QTreeWidgetItem *it = ui->treeFile->topLevelItem(i);
        changeItemCaption(it);
    }
}


void MainWindow::on_actZoomIn_triggered()
{
    ratio_ *= 1.2;
    spinRatio->setValue(100 * ratio_);
    int w = ratio_ * pixmap_.width();
    int h = ratio_ * pixmap_.height();
    QPixmap pix = pixmap_.scaled(w, h);
    ui->labPic->setPixmap(pix);
}


void MainWindow::on_actZoomOut_triggered()
{
    ratio_ *= 0.8;
    spinRatio->setValue(100 * ratio_);
    int w = ratio_ * pixmap_.width();
    int h = ratio_ * pixmap_.height();
    QPixmap pix = pixmap_.scaled(w, h);
    ui->labPic->setPixmap(pix);
}


void MainWindow::on_actFitReal_triggered()
{
    ratio_ = 1;
    spinRatio->setValue(100);
    ui->labPic->setPixmap(pixmap_);
}


void MainWindow::on_actFitW_triggered()
{
    int W = ui->scrollArea->width();
    int realW = pixmap_.width();       // 原始图片实际高度
    ratio_ = float(W) /realW;
    spinRatio->setValue(100 * ratio_);
    QPixmap pix = pixmap_.scaledToHeight(W-30);     // ???why minus 30
    ui->labPic->setPixmap(pix);
}


void MainWindow::on_actFitH_triggered()
{
    int H = ui->scrollArea->height();
    int realH = pixmap_.height();       // 原始图片实际高度
    ratio_ = float(H) /realH;
    spinRatio->setValue(100 * ratio_);
    QPixmap pix = pixmap_.scaledToHeight(H-30);     // ???
    ui->labPic->setPixmap(pix);
}


void MainWindow::on_actFloat_triggered()
{

}

// 设置停靠区浮动属性
void MainWindow::on_actFloat_triggered(bool checked)
{
    ui->dockWidget->setFloating(checked);
}

// 设置停靠区可见属性
void MainWindow::on_actVisiable_triggered(bool checked)
{
    ui->dockWidget->setVisible(checked);
}

// 停靠区浮动状态变化
void MainWindow::on_dockWidget_topLevelChanged(bool topLevel)
{
    ui->actFloat->setChecked(topLevel);
}

// 停靠区可见性状态变化
void MainWindow::on_dockWidget_visibilityChanged(bool visible)
{
    ui->actVisiable->setChecked(visible);
}


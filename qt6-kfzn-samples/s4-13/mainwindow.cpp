#include "mainwindow.h"
#include "ui_mainwindow.h"
#include    <QDate>
#include    <QTableWidgetItem>
#include    <QRandomGenerator>

void MainWindow::createItemsARow(int rowNo, QString name, QString sex, QDate birth, QString nation, bool isPM, int score) {
    uint studID = 20210500;

    // 姓名
    QTableWidgetItem *it = new QTableWidgetItem(name, ctName);
    it->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    studID += rowNo;
    it->setData(Qt::UserRole, QVariant(studID));    // 学号不显示在table中，但是与单元格相关联
    ui->tabInfo->setItem(rowNo, colName, it);

    // 性别
    QIcon icon;
    if (sex == "男")
        icon.addFile(":/images/icons/boy.ico");
    else
        icon.addFile(":/images/icons/girl.ico");
    it = new QTableWidgetItem(sex, ctSex);
    it->setIcon(icon);
    it->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    Qt::ItemFlags flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    it->setFlags(flags);
    ui->tabInfo->setItem(rowNo, colSex, it);

    // 出生日期
    QString str = birth.toString("yyyy-MM-dd");
    it = new QTableWidgetItem(str, ctBirth);
    ui->tabInfo->setItem(rowNo, colBirth, it);

    // 民族
    it = new QTableWidgetItem(nation, ctNation);
    it->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tabInfo->setItem(rowNo, colNation, it);

    // 是否党员
    it = new QTableWidgetItem("党员", ctPartyM);
    it->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;     // 不允许编辑，但是可以复选
    it->setFlags(flags);
    if (isPM)
        it->setCheckState(Qt::Checked);
    else
        it->setCheckState(Qt::Unchecked);
    it->setBackground(QBrush(Qt::yellow));
    ui->tabInfo->setItem(rowNo, colPartyM, it);

    // 分数
    str.setNum(score);
    it = new QTableWidgetItem(str, ctScore);
    it->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tabInfo->setItem(rowNo, colScore, it);

}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter_2);

    labCellIndex = new QLabel("当前单元格坐标： ", this);
    labCellIndex->setMinimumWidth(250);
    labCellType = new QLabel("当前单元格类型： ", this);
    labCellType->setMinimumWidth(200);
    labStudId = new QLabel("学生 ID： ", this);
    labStudId->setMinimumWidth(200);

    ui->statusbar->addWidget(labCellIndex);
    ui->statusbar->addWidget(labCellType);
    ui->statusbar->addWidget(labStudId);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 设置表头
void MainWindow::on_btnSetHeader_clicked()
{
    QStringList head_txt;
    head_txt << "姓名" << "性别" << "出生日期" << "民族" << "分数" << "是否党员";

    ui->tabInfo->setColumnCount(head_txt.size());
    for (int i = 0; i < ui->tabInfo->columnCount(); i++) {
        QTableWidgetItem *header_item = new QTableWidgetItem(head_txt.at(i));
        QFont font = header_item->font();
        font.setBold(true);
        font.setPointSize(11);
        header_item->setForeground(QBrush(Qt::red));
        header_item->setFont(font);
        ui->tabInfo->setHorizontalHeaderItem(i, header_item);
    }
}

// 初始化表格数据
void MainWindow::on_btnInitData_clicked()
{
    QDate birth(2001,4,6);
    ui->tabInfo->clearContents();
    for (int i = 0; i < ui->tabInfo->rowCount(); i++) {
        QString name = QString("学生 %1").arg(i);
        QString sex = (i%2 == 0) ? "男" : "女";
        bool is_party = (i%2==0) ? false : true;
        int score = QRandomGenerator::global()->bounded(60, 100);   // 随机范围[60, 100)
        createItemsARow(i, name, sex, birth, "汉", is_party, score);
        birth = birth.addDays(20);
    }
}


void MainWindow::on_tabInfo_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    Q_UNUSED(previousRow);
    Q_UNUSED(previousColumn);
    QTableWidgetItem *it = ui->tabInfo->item(currentRow, currentColumn);
    if (it == nullptr)
        return;

    labCellIndex->setText(QString::asprintf("当前单元格坐标：%d 行，%d 列", currentRow, currentColumn));

    int cell_type = it->type();
    labCellType->setText(QString::asprintf("当前单元格类型：%d", cell_type));

    it = ui->tabInfo->item(currentRow, colName);
    uint id = it->data(Qt::UserRole).toUInt();
    labStudId->setText(QString::asprintf("学生 ID: %d", id));
}


void MainWindow::on_btnInsertRow_clicked()
{
    int cur_row = ui->tabInfo->currentRow();
    ui->tabInfo->insertRow(cur_row);
    createItemsARow(cur_row, "新学生", "男", QDate::fromString("2022-10-1","yyyy-M-d"), "苗族", false, 89);
}


void MainWindow::on_btnAppendRow_clicked()
{
    int cur_row = ui->tabInfo->rowCount();
    ui->tabInfo->insertRow(cur_row);
    createItemsARow(cur_row, "新学生", "女", QDate::fromString("2032-10-1","yyyy-M-d"), "满族", false, 66);
}


void MainWindow::on_btnDelCurRow_clicked()
{
    int cur_row = ui->tabInfo->currentRow();
    ui->tabInfo->removeRow(cur_row);
}


void MainWindow::on_btnAutoH_clicked()
{
    ui->tabInfo->resizeRowsToContents();
}


void MainWindow::on_btnAutoW_clicked()
{
    ui->tabInfo->resizeColumnsToContents();
}


void MainWindow::on_btnSetRow_clicked()
{
    ui->tabInfo->setRowCount(ui->spinLineNum->value());
}


void MainWindow::on_chkTabEditable_clicked(bool checked)
{
    if (checked)
        ui->tabInfo->setEditTriggers(QAbstractItemView::DoubleClicked |
                                     QAbstractItemView::SelectedClicked);
    else
        ui->tabInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void MainWindow::on_chkRowColor_clicked(bool checked)
{
    ui->tabInfo->setAlternatingRowColors(checked);
}

// 竖直表头
void MainWindow::on_chkShowHeaderV_clicked(bool checked)
{
    ui->tabInfo->verticalHeader()->setVisible(checked);
}

// 水平表头
void MainWindow::on_chkShowHeader_clicked(bool checked)
{
    ui->tabInfo->horizontalHeader()->setVisible(checked);
}


void MainWindow::on_rBtnSelRow_clicked()
{
    ui->tabInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
}


void MainWindow::on_rBtnSelItem_clicked()
{
    ui->tabInfo->setSelectionBehavior(QAbstractItemView::SelectItems);
}


void MainWindow::on_btnReadTab_clicked()
{
    QTableWidgetItem *it;
    ui->textEdit->clear();

    for (int i = 0; i < ui->tabInfo->rowCount(); ++i) {
        QString str = QString::asprintf("第%d行：", i + 1);
        for (int j = 0; j < ui->tabInfo->columnCount()-1; j++) {
            it = ui->tabInfo->item(i, j);
            str += it->text() + " ";
        }
        it = ui->tabInfo->item(i, colPartyM);
        if (it->checkState() == Qt::Checked)
            str += "党员";
        else
            str += "群众";
        ui->textEdit->append(str);
    }
}


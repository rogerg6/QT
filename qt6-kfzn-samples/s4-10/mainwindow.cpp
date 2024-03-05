#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buildUI();
    buildSingnalSlots();

    ui->toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buildUI() {
    // 创建状态栏上的组件
    labFile = new QLabel(this);
    labFile->setMinimumWidth(150);
    labFile->setText("文件名：");
    ui->statusbar->addWidget(labFile);

    progBar = new QProgressBar(this);
    progBar->setMaximumWidth(200);
    progBar->setMinimum(5);
    progBar->setMaximum(50);
    progBar->setValue(ui->textEdit->font().pointSize());
    ui->statusbar->addWidget(progBar);

    labInfo = new QLabel(this);
    labInfo->setText("字体名称：");
    ui->statusbar->addPermanentWidget(labInfo);

    // 设置actionCN和actionEN互斥选择
    act_grp = new QActionGroup(this);
    act_grp->addAction(ui->actionCN);
    act_grp->addAction(ui->actionEN);
    act_grp->setExclusive(true);
    ui->actionCN->setChecked(true);

    // 创建工具栏上无法可视化设计的组件
    spinFontSize = new QSpinBox(this);
    spinFontSize->setMinimum(5);
    spinFontSize->setMaximum(50);
    spinFontSize->setValue(ui->textEdit->font().pointSize());
    spinFontSize->setMinimumWidth(50);
    ui->toolBar->addWidget(spinFontSize);

    comboFontName = new QFontComboBox(this);
    comboFontName->setMinimumWidth(150);
    ui->toolBar->addWidget(comboFontName);

    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actionColse);
}

void  MainWindow::buildSingnalSlots(){
    connect(spinFontSize, SIGNAL(valueChanged(int)), this, SLOT(do_fontSize_changed(int)));
    connect(comboFontName, &QFontComboBox::currentFontChanged, this, &MainWindow::do_fontSelected);
}

void MainWindow::do_fontSize_changed(int fontSize) {
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setFontPointSize(fontSize);
    ui->textEdit->mergeCurrentCharFormat(fmt);
    progBar->setValue(fontSize);
}

void MainWindow::do_fontSelected(const QFont &font) {
    labInfo->setText("字体名称：" + font.family());
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setFont(font);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}


void MainWindow::on_actionNew_triggered()
{
    ui->textEdit->clear();
    ui->textEdit->document()->setModified(false);
    labFile->setText("新建一个文件");
}


void MainWindow::on_actionOpen_triggered()
{
    labFile->setText("打开一个文件");
}


void MainWindow::on_actionSave_triggered()
{
    ui->textEdit->document()->setModified(false);
    labFile->setText("保存文件");
}


void MainWindow::on_actionColse_triggered()
{

}


void MainWindow::on_actionBold_triggered()
{

}


void MainWindow::on_actionBold_triggered(bool checked)
{

    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    if (checked) {
        fmt.setFontWeight(QFont::Bold);
    }else {
        fmt.setFontWeight(QFont::Normal);
    }
    ui->textEdit->mergeCurrentCharFormat(fmt);
}


void MainWindow::on_actionItalic_triggered(bool checked)
{
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setFontItalic(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}


void MainWindow::on_actionUnderline_triggered(bool checked)
{
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setFontUnderline(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}


void MainWindow::on_actionToggleText_triggered(bool checked)
{
    if (checked)
        ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    else
        ui->toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
}


void MainWindow::on_textEdit_selectionChanged()
{
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    ui->actionBold->setChecked(fmt.font().bold());
    ui->actionItalic->setChecked(fmt.fontItalic());
    ui->actionUnderline->setChecked(fmt.fontUnderline());
}


void MainWindow::on_textEdit_copyAvailable(bool b)
{
    ui->actionCut->setEnabled(b);
    ui->actionCopy->setEnabled(b);
    ui->actionPaste->setEnabled(ui->textEdit->canPaste());
}


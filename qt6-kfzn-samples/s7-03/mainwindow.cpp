#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPixmap>

#include "formdoc.h"
#include "formtable.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear();
    ui->tabWidget->setTabsClosable(true);
    this->setCentralWidget(ui->tabWidget);
    this->setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.drawPixmap(0, ui->toolBar->height(), this->width(),\
              this->height()-ui->toolBar->height()-ui->statusbar->height(), \
                 QPixmap(":/icons/images/back2.jpg"));
}


void MainWindow::do_changeTabTile(QString title) {
    int index = ui->tabWidget->currentIndex();
    ui->tabWidget->setTabText(index, title);
}

void MainWindow::on_actiEmbedWidget_triggered()
{
    FormDoc *formdoc = new FormDoc(this);
    formdoc->setAttribute(Qt::WA_DeleteOnClose, true);
    int cur = ui->tabWidget->addTab(formdoc, \
                 QString::asprintf("Doc %d", ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
    connect(formdoc, &FormDoc::titleChanged, this, &MainWindow::do_changeTabTile);
}


void MainWindow::on_actAloneWidget_triggered()
{
    FormDoc *formdoc = new FormDoc();       // 独立窗口，不设置父类，用show()显示
    formdoc->setAttribute(Qt::WA_DeleteOnClose, true);
    formdoc->setWindowTitle("基于QWidget的窗口，无父窗口，关闭时删除");
    formdoc->setWindowOpacity(0.9);
    formdoc->setWindowFlag(Qt::Window, true);   // 代表是个窗口
    formdoc->show();
}


void MainWindow::on_actEmbedMainWindow_triggered()
{
    FormTable *ft = new FormTable(this);
    ft->setAttribute(Qt::WA_DeleteOnClose);
    int cur = ui->tabWidget->addTab(ft, QString::asprintf("Table %d", ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}


void MainWindow::on_actiAloneMainWindow_triggered()
{
    FormTable *ft = new FormTable(this);
    ft->setAttribute(Qt::WA_DeleteOnClose);
    ft->setWindowTitle("基于QMainWindow的窗口");
    ft->statusBar();        // 如果没有状态栏，就创建状态栏
    ft->show();
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    Q_UNUSED(index);
    bool en = ui->tabWidget->count() > 0;
    ui->tabWidget->setVisible(en);
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if (index < 0)
        return;
    QWidget *form = ui->tabWidget->widget(index);
    form->close();
}


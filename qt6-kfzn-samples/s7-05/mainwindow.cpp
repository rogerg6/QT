#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QMdiArea>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mdiArea->setTabsClosable(true);     // 页面可关闭
    ui->mdiArea->setTabsMovable(true);     // 页面可移动
    setCentralWidget(ui->mdiArea);
    setWindowState(Qt::WindowMaximized);
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    ui->actCut->setEnabled(false);
    ui->actCopy->setEnabled(false);
    ui->actPaste->setEnabled(false);
    ui->actFont->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actNew_triggered()
{
    FormDoc *formdoc = new FormDoc(this);
    ui->mdiArea->addSubWindow(formdoc);
    formdoc->show();
    ui->actCut->setEnabled(true);
    ui->actCopy->setEnabled(true);
    ui->actPaste->setEnabled(true);
    ui->actFont->setEnabled(true);
}


void MainWindow::on_actOpen_triggered()
{
    bool need_new = false;          // 是否需要新建子窗口
    FormDoc *formdoc;
    if (ui->mdiArea->subWindowList().size() > 0) {
        formdoc = (FormDoc*)ui->mdiArea->activeSubWindow()->widget();
        need_new = formdoc->isFileOpened();
    }
    else
        need_new = true;

    QString cur_path = QDir::currentPath();
    QString filename = QFileDialog::getOpenFileName(this, tr("打开一个文件"), cur_path, \
                        "C程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)");
    if (filename.isEmpty())
        return;

    if (need_new) {
        formdoc = new FormDoc(this);
        ui->mdiArea->addSubWindow(formdoc);
    }

    // 打开文件
    formdoc->loadFromFile(filename);
    formdoc->show();
    ui->actCut->setEnabled(true);
    ui->actCopy->setEnabled(true);
    ui->actPaste->setEnabled(true);
    ui->actFont->setEnabled(true);
}



void MainWindow::on_actCloseAll_triggered()
{
    ui->mdiArea->closeAllSubWindows();
}


void MainWindow::on_actCascade_triggered()
{
    ui->mdiArea->cascadeSubWindows();
}


void MainWindow::on_actTile_triggered()
{
    ui->mdiArea->tileSubWindows();
}




void MainWindow::on_actMDI_triggered(bool checked)
{
    if (checked)
        ui->mdiArea->setViewMode(QMdiArea::TabbedView);
    else
        ui->mdiArea->setViewMode(QMdiArea::SubWindowView);
    ui->mdiArea->setTabsClosable(checked);
    ui->actCascade->setEnabled(!checked);
    ui->actTile->setEnabled(!checked);
}


void MainWindow::on_actSave_triggered()
{
    FormDoc *formdoc = (FormDoc*)ui->mdiArea->activeSubWindow()->widget();
    formdoc->saveToFile();
}


void MainWindow::on_actCut_triggered()
{
    FormDoc *formdoc = (FormDoc*)ui->mdiArea->activeSubWindow()->widget();
    formdoc->textCut();
}


void MainWindow::on_actCopy_triggered()
{
    FormDoc *formdoc = (FormDoc*)ui->mdiArea->activeSubWindow()->widget();
    formdoc->textCopy();
}


void MainWindow::on_actPaste_triggered()
{
    FormDoc *formdoc = (FormDoc*)ui->mdiArea->activeSubWindow()->widget();
    formdoc->textPaste();
}


void MainWindow::on_actFont_triggered()
{
    FormDoc *formdoc = (FormDoc*)ui->mdiArea->activeSubWindow()->widget();
    formdoc->setEditFont();
}


void MainWindow::on_mdiArea_subWindowActivated(QMdiSubWindow *arg1)
{
    if (ui->mdiArea->subWindowList().size() == 0 ) {
        ui->actCut->setEnabled(false);
        ui->actCopy->setEnabled(false);
        ui->actPaste->setEnabled(false);
        ui->actFont->setEnabled(false);
        ui->statusbar->clearMessage();
    } else {
        FormDoc *form_doc = static_cast<FormDoc*>(arg1->widget());
        ui->statusbar->showMessage(form_doc->currentFileName());
    }
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QSaveFile>
#include <QException>
#include <QTextBlock>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setTabsClosable(false); // 不允许关闭tab页
    ui->tabWidget->setDocumentMode(true); // 文档模式，去掉了边框
    this->setCentralWidget(ui->tabWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// QFile打开
void MainWindow::on_actionQFileOpen_triggered()
{
    QString cur_path = QDir::currentPath();
    QString title = "打开一个文件";
    QString filter = "程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)";
    QString filename = QFileDialog::getOpenFileName(this, title, cur_path, filter);
    if (filename.isEmpty())
        return;

    QFileInfo file_info(filename);
    QDir::setCurrent(file_info.absolutePath());  // 设置应用程序当前目录
    openByIO_Whole(filename);   // 全部读取
}

// 全部读取
bool MainWindow::openByIO_Whole(const QString &filename) {
    QFile file(filename);
    if (!file.exists())
        return false;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QByteArray all_lines = file.readAll();
    QString text(all_lines);
    ui->textQFile->setPlainText(text);
    file.close();
    ui->tabWidget->setCurrentIndex(0);
    return true;
}

// 按行读取
bool MainWindow::openByIO_Lines(const QString &filename) {
    QFile file(filename);
    if (!file.exists())
        return false;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    ui->textQFile->clear();
    while (!file.atEnd()) {
        QByteArray line = file.readLine();  // 读取一行，末尾自动添加'\0'
        QString str(line);
        str.truncate(str.length() - 1);  // 去除'\0'
        ui->textQFile->appendPlainText(str);
    }
    file.close();
    ui->tabWidget->setCurrentIndex(0);
    return true;
}

// QFile另存
void MainWindow::on_actionQFileSaveAs_triggered()
{
    QString cur_path = QDir::currentPath();
    QString title = "另存为一个文件";
    QString filter = "程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)";
    QString filename = QFileDialog::getSaveFileName(this, title, cur_path, filter);
    if (filename.isEmpty())
        return;

    QFileInfo file_info(filename);
    QDir::setCurrent(file_info.absolutePath());  // 设置应用程序当前目录
    saveByIO_Whole(filename);
}

bool MainWindow::saveByIO_Whole(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QString str = ui->textQFile->toPlainText();   // 整个内容作为字符串
    QByteArray str_bytes = str.toUtf8();
    file.write(str_bytes, str_bytes.length());
    file.close();
    ui->tabWidget->setCurrentIndex(0);
    return true;
}

// QSaveFIle另存
void MainWindow::on_actionQSaveFileSaveAs_triggered()
{
    QString cur_path = QDir::currentPath();
    QString title = "另存为一个文件";
    QString filter = "程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)";
    QString filename = QFileDialog::getSaveFileName(this, title, cur_path, filter);
    if (filename.isEmpty())
        return;

    QFileInfo file_info(filename);
    QDir::setCurrent(file_info.absolutePath());  // 设置应用程序当前目录
    saveByIO_Safe(filename);
}

// 用QSaveFile保存，安全保存，如果保存出问题，不会写入目标文件
bool MainWindow::saveByIO_Safe(const QString &filename) {
    QSaveFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    file.setDirectWriteFallback(false);     // 使用临时文件
    try {
        QString str = ui->textQFile->toPlainText();   // 整个内容作为字符串
        QByteArray str_bytes = str.toUtf8();
        file.write(str_bytes, str_bytes.length());
        file.commit();      // 提交对文件的修改
        ui->tabWidget->setCurrentIndex(0);
        return true;
    } catch (QException e) {
        qDebug("保存文件的过程中发生了错误");
        file.cancelWriting();
        return false;
    }
}

// 用QTextStream打开
void MainWindow::on_actionQTextStreamOpen_triggered()
{
    QString cur_path = QDir::currentPath();
    QString title = "打开一个文件";
    QString filter = "程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)";
    QString filename = QFileDialog::getOpenFileName(this, title, cur_path, filter);
    if (filename.isEmpty())
        return;

    QFileInfo file_info(filename);
    QDir::setCurrent(file_info.absolutePath());  // 设置应用程序当前目录
    openByStream_Whole(filename);   // 全部读取
}

bool MainWindow::openByStream_Whole(const QString &filename){
    QFile file(filename);
    if (!file.exists())
        return false;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream strm(&file);
    strm.setAutoDetectUnicode(true);

    QString str = strm.readAll();
    ui->textQTextStream->setPlainText(str);
    file.close();
    ui->tabWidget->setCurrentIndex(1);
    return true;
}

bool MainWindow::openByStream_Lines(const QString &filename){
    QFile file(filename);
    if (!file.exists())
        return false;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream strm(&file);
    strm.setAutoDetectUnicode(true);
    ui->textQTextStream->clear();
    while (!strm.atEnd()) {
        QString line = file.readLine();
        ui->textQFile->appendPlainText(line);
    }
    file.close();
    ui->tabWidget->setCurrentIndex(1);
    return true;
}


// QTextStream另存
void MainWindow::on_actionQTextStreamSaveAs_triggered()
{
    QString cur_path = QDir::currentPath();
    QString title = "另存为一个文件";
    QString filter = "程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)";
    QString filename = QFileDialog::getSaveFileName(this, title, cur_path, filter);
    if (filename.isEmpty())
        return;

    QFileInfo file_info(filename);
    QDir::setCurrent(file_info.absolutePath());  // 设置应用程序当前目录
    saveByStream_Safe(filename);
}

bool MainWindow::saveByStream_Whole(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream strm(&file);
    strm.setAutoDetectUnicode(true);

    QString str = ui->textQFile->toPlainText();   // 整个内容作为字符串
    strm << str;
    file.close();
    return true;
}

bool MainWindow::saveByStream_Safe(const QString &filename){
    QSaveFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    file.setDirectWriteFallback(false);     // 使用临时文件
    try {
        // 逐段保存
        QTextStream strm(&file);
        strm.setAutoDetectUnicode(true);
        QTextDocument *doc = ui->textQTextStream->document();
        int cnt = doc->blockCount();
        for (int i = 0; i < cnt; i++) {
            QTextBlock line = doc->findBlockByLineNumber(i);
            QString str = line.text();
            strm << str << "\n";
        }
        file.commit();      // 提交对文件的修改232
        return true;
    } catch (QException e) {
        qDebug("保存文件的过程中发生了错误");
        file.cancelWriting();
        return false;
    }
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include    <QFloat16>
#include <QFontDialog>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox->setEnabled(false);    // 刚启动，禁用数据读写分组框
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnTestFile_clicked()
{
    QString cur_path = QDir::currentPath();
    filename_ = QFileDialog::getOpenFileName(this, "打开一个文件", cur_path, "流数据文件(*.raw)");
    if (!filename_.isEmpty()) {
        ui->lineEditFile->setText(filename_);
        ui->groupBox->setEnabled(true);
        ui->actionReadCon->setEnabled(true);
        ui->actionWriteCon->setEnabled(true);
    }
}

bool MainWindow::iniWrite(){
    file_dev_ = new QFile(filename_);
    if (!file_dev_->open(QIODevice::WriteOnly))
        return false;

    file_strm_ = new QDataStream(file_dev_);
    file_strm_->setVersion(QDataStream::Qt_6_2);     //读写版本必须兼容
    if (ui->rBtnLE->isChecked())
        file_strm_->setByteOrder(QDataStream::LittleEndian);
    else
        file_strm_->setByteOrder(QDataStream::BigEndian);

    if (ui->rBtnSingle->isChecked())
        file_strm_->setFloatingPointPrecision(QDataStream::SinglePrecision);
    else
        file_strm_->setFloatingPointPrecision(QDataStream::DoublePrecision);

    return true;
}

bool MainWindow::iniRead(){
    if (!QFile::exists(filename_)) {
        QMessageBox::critical(this, "错误", "文件不存在，文件名：\n" + filename_);
        return false;
    }
    file_dev_ = new QFile(filename_);
    if (!file_dev_->open(QIODevice::ReadOnly))
        return false;

    file_strm_ = new QDataStream(file_dev_);
    file_strm_->setVersion(QDataStream::Qt_6_2);     //读写版本必须兼容
    if (ui->rBtnLE->isChecked())
        file_strm_->setByteOrder(QDataStream::LittleEndian);
    else
        file_strm_->setByteOrder(QDataStream::BigEndian);

    if (ui->rBtnSingle->isChecked())
        file_strm_->setFloatingPointPrecision(QDataStream::SinglePrecision);
    else
        file_strm_->setFloatingPointPrecision(QDataStream::DoublePrecision);

    return true;
}

void MainWindow::delFileStream(){
    file_dev_->close();
    delete file_strm_;
    delete file_dev_;
}


void MainWindow::on_btnInt8Write_clicked()
{
    if (iniWrite()) {
        qint8 value = ui->spinInt8->value();
        file_strm_->writeRawData((char*)&value, sizeof(qint8));
        delFileStream();
    }
}


void MainWindow::on_btnUint8Write_clicked()
{
    if (iniWrite()) {
        quint8 value = ui->spinUint8->value();
        file_strm_->writeRawData((char*)&value, sizeof(quint8));
        delFileStream();
    }
}


void MainWindow::on_btnInt16Write_clicked()
{
    if (iniWrite()) {
        qint16 value = ui->spinInt16->value();
        file_strm_->writeRawData((char*)&value, sizeof(qint16));
        delFileStream();
    }

}


void MainWindow::on_btnUint16Write_clicked()
{
    if (iniWrite()) {
        quint16 value = ui->spinUint16->value();
        file_strm_->writeRawData((char*)&value, sizeof(quint16));
        delFileStream();
    }
}


void MainWindow::on_btnInt32Write_clicked()
{
    if (iniWrite()) {
        qint32 value = ui->spinInt32->value();
        file_strm_->writeRawData((char*)&value, sizeof(qint32));
        delFileStream();
    }
}


void MainWindow::on_btnInt64Write_clicked()
{
    if (iniWrite()) {
        qint64 value = ui->spinInt64->value();
        file_strm_->writeRawData((char*)&value, sizeof(qint64));
        delFileStream();
    }
}


void MainWindow::on_btnBoolWrite_clicked()
{
    if (iniWrite()) {
        bool value = ui->chkBoolIn->isChecked();
        file_strm_->writeRawData((char*)&value, sizeof(bool));
        delFileStream();
    }
}


void MainWindow::on_btnFloat16Write_clicked()
{
    if (iniWrite()) {
        qfloat16 value = ui->spinFloat16->value();
        file_strm_->writeRawData((char*)&value, sizeof(qfloat16));
        delFileStream();
    }

}


void MainWindow::on_btnFloatWrite_clicked()
{
    if (iniWrite()) {
        float value = ui->spinFloat->value();
        file_strm_->writeRawData((char*)&value, sizeof(float));
        delFileStream();
    }
}


void MainWindow::on_btnDoubleWrite_clicked()
{
    if (iniWrite()) {
        double value = ui->spinDouble->value();
        file_strm_->writeRawData((char*)&value, sizeof(double));
        delFileStream();
    }
}


void MainWindow::on_btnUtfStrWrite_clicked()
{
    if (iniWrite()) {
        QString str = ui->editUtfStrIn->text();
        QByteArray btarr = str.toUtf8();
        file_strm_->writeBytes(btarr, btarr.length());
        delFileStream();
    }
}

void MainWindow::on_btnLatinStrWrite_clicked()
{
    if (iniWrite()) {
        QString str = ui->editLatinStrIn->text();
        QByteArray btarr = str.toLatin1();
        file_strm_->writeBytes(btarr, btarr.length());
        delFileStream();
    }
}

void MainWindow::on_btnInt8Read_clicked()
{
    if (iniRead()) {
        qint8 value = 0;
        file_strm_->readRawData((char*)&value, sizeof(qint8));
        ui->editInt8Out->setText(QString("%1").arg(value));
        delFileStream();
    }
}


void MainWindow::on_btnUint8Read_clicked()
{
    if (iniRead()) {
        quint8 value = 0;
        file_strm_->readRawData((char*)&value, sizeof(quint8));
        ui->editUint8Out->setText(QString("%1").arg(value));
        delFileStream();
    }
}


void MainWindow::on_btnInt16Read_clicked()
{
    if (iniRead()) {
        qint16 value = 0;
        file_strm_->readRawData((char*)&value, sizeof(qint16));
        ui->editInt16Out->setText(QString("%1").arg(value));
        delFileStream();
    }

}


void MainWindow::on_btnUint16Read_clicked()
{
    if (iniRead()) {
        quint16 value = 0;
        file_strm_->readRawData((char*)&value, sizeof(quint16));
        ui->editUint16Out->setText(QString("%1").arg(value));
        delFileStream();
    }
}


void MainWindow::on_btnInt32Read_clicked()
{
    if (iniRead()) {
        qint32 value = 0;
        file_strm_->readRawData((char*)&value, sizeof(qint32));
        ui->editInt32Out->setText(QString("%1").arg(value));
        delFileStream();
    }

}


void MainWindow::on_btnInt64Read_clicked()
{
    if (iniRead()) {
        qint64 value = 0;
        file_strm_->readRawData((char*)&value, sizeof(qint64));
        ui->editInt64Out->setText(QString("%1").arg(value));
        delFileStream();
    }
}


void MainWindow::on_btnBoolRead_clicked()
{
    if (iniRead()) {
        bool value = 0;
        file_strm_->readRawData((char*)&value, sizeof(bool));
        ui->chkBoolOut->setChecked(value);
        delFileStream();
    }
}


void MainWindow::on_btnFloat16Read_clicked()
{
    if (iniRead()) {
        qfloat16 value = 0;
        file_strm_->readRawData((char*)&value, sizeof(qfloat16));
        ui->editFloat16Out->setText(QString("%1").arg(value));
        delFileStream();
    }

}


void MainWindow::on_btnFloatRead_clicked()
{
    if (iniRead()) {
        float value = 0;
        file_strm_->readRawData((char*)&value, sizeof(float));
        ui->editFloatOut->setText(QString("%1").arg(value));
        delFileStream();
    }
}


void MainWindow::on_btnDoubleRead_clicked()
{
    if (iniRead()) {
        double value = 0;
        file_strm_->readRawData((char*)&value, sizeof(double));
        ui->editDoubleOut->setText(QString("%1").arg(value));
        delFileStream();
    }
}


void MainWindow::on_btnUtfStrRead_clicked()
{
    if (iniRead()) {
        char *buf;
        uint len;
        file_strm_->readBytes(buf, len);
        QString str = QString::fromUtf8(buf, len);
        ui->editUtfStrOut->setText(str);
        delFileStream();
        delete buf;     // 需要手动删除
        QString info = QString("读出数据缓冲区长度 = %1 字节").arg(len);
        QMessageBox::information(this, "信息提示", info);
    }
}


void MainWindow::on_btnLatinStrRead_clicked()
{
    if (iniRead()) {
        char *buf;
        uint len;
        file_strm_->readBytes(buf, len);
        QString str = QString::fromLatin1(buf, len);
        ui->editLatinStrOut->setText(str);
        delFileStream();
        delete buf;     // 需要手动删除
        QString info = QString("读出数据缓冲区长度 = %1 字节").arg(len);
        QMessageBox::information(this, "信息提示", info);
    }
}


void MainWindow::on_actionEditClear_triggered()
{

}


void MainWindow::on_actionWriteCon_triggered()
{
    if (!iniWrite())
        return;

    qint8 value = ui->spinInt8->value();
    file_strm_->writeRawData((char*)&value, sizeof(qint8));

    quint8 v = ui->spinUint8->value();
    file_strm_->writeRawData((char*)&v, sizeof(quint8));

    QString str = ui->editUtfStrIn->text();
    QByteArray btarr = str.toUtf8();
    file_strm_->writeBytes(btarr, btarr.length());

    //... 连续写入不同类型的值

    delFileStream();
    QMessageBox::information(this, "消息", "数据连续写入文件完成");
}


void MainWindow::on_actionReadCon_triggered()
{
    if (!iniRead()) {
        return;
    }

    qint8 value = 0;
    file_strm_->readRawData((char*)&value, sizeof(qint8));
    ui->editInt8Out->setText(QString("%1").arg(value));

    quint8 v = 0;
    file_strm_->readRawData((char*)&value, sizeof(quint8));
    ui->editUint8Out->setText(QString("%1").arg(v));

    char *buf;
    uint len;
    file_strm_->readBytes(buf, len);
    QString str = QString::fromUtf8(buf, len);
    ui->editUtfStrOut->setText(str);
    delete buf;     // 需要手动删除

     //... 连续读取不同类型的值

    delFileStream();
    QMessageBox::information(this, "消息", "从文件连续读取数据完成");
}


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
    filename_ = QFileDialog::getOpenFileName(this, "打开一个文件", cur_path, "流数据文件(*.stream)");
    if (!filename_.isEmpty()) {
        ui->lineEditFile->setText(filename_);
        ui->groupBox->setEnabled(true);
        ui->actionReadCon->setEnabled(true);
        ui->actionWriteCon->setEnabled(true);
    }
}

template<class T>
void MainWindow::writeByStream(T value){
    QFile file_dev(filename_);
    if (!file_dev.open(QIODevice::WriteOnly))
        return;

    QDataStream file_strm(&file_dev);
    file_strm.setVersion(QDataStream::Qt_6_2);     //读写版本必须兼容
    if (ui->rBtnLE->isChecked())
        file_strm.setByteOrder(QDataStream::LittleEndian);
    else
        file_strm.setByteOrder(QDataStream::BigEndian);

    if (ui->rBtnSingle->isChecked())
        file_strm.setFloatingPointPrecision(QDataStream::SinglePrecision);
    else
        file_strm.setFloatingPointPrecision(QDataStream::DoublePrecision);
    file_strm << value;
    file_dev.close();
}

template<class T>
void MainWindow::readByStream(T &value) {
    if (!QFile::exists(filename_)) {
        QMessageBox::critical(this, "错误", "文件不存在，文件名：\n" + filename_);
        return;
    }
    QFile file_dev(filename_);
    if (!file_dev.open(QIODevice::ReadOnly))
        return;

    QDataStream file_strm(&file_dev);
    file_strm.setVersion(QDataStream::Qt_6_2);     //读写版本必须兼容
    if (ui->rBtnLE->isChecked())
        file_strm.setByteOrder(QDataStream::LittleEndian);
    else
        file_strm.setByteOrder(QDataStream::BigEndian);

    if (ui->rBtnSingle->isChecked())
        file_strm.setFloatingPointPrecision(QDataStream::SinglePrecision);
    else
        file_strm.setFloatingPointPrecision(QDataStream::DoublePrecision);
    file_strm >> value;
    file_dev.close();
};


void MainWindow::on_btnInt8Write_clicked()
{
    qint8 value = ui->spinInt8->value();
    writeByStream(value);
}


void MainWindow::on_btnUint8Write_clicked()
{
    quint8 value = ui->spinUint8->value();
    writeByStream(value);
}


void MainWindow::on_btnInt16Write_clicked()
{
    qint16 value = ui->spinInt16->value();
    writeByStream(value);
}


void MainWindow::on_btnUint16Write_clicked()
{
    quint16 value = ui->spinUint16->value();
    writeByStream(value);
}


void MainWindow::on_btnInt32Write_clicked()
{
    qint32 value = ui->spinInt32->value();
    writeByStream(value);
}


void MainWindow::on_btnInt64Write_clicked()
{
    qint64 value = ui->spinInt64->value();
    writeByStream(value);
}


void MainWindow::on_btnBoolWrite_clicked()
{
    bool value = ui->chkBoolIn->isChecked();
    writeByStream(value);
}


void MainWindow::on_btnFloat16Write_clicked()
{
    qfloat16 value = ui->spinFloat16->value();
    writeByStream(value);
}


void MainWindow::on_btnFloatWrite_clicked()
{
    float value = ui->spinFloat->value();
    writeByStream(value);
}


void MainWindow::on_btnDoubleWrite_clicked()
{
    double value = ui->spinDouble->value();
    writeByStream(value);
}


void MainWindow::on_btnStrWrite_clicked()
{
    QString str = ui->editStrIn->text();
    char *value = str.toLocal8Bit().data();
    writeByStream(value);
}

void MainWindow::on_btnQStrWrite_clicked()
{
    QString str = ui->editQStrIn->text();
    writeByStream(str);
}

void MainWindow::on_btnFontIn_clicked()
{
    QFont font = ui->btnFontIn->font();
    bool ok = false;
    font = QFontDialog::getFont(&ok, font, this);
    if (ok)
        ui->btnFontIn->setFont(font);
}


void MainWindow::on_btnFontWrite_clicked()
{
    QFont font = ui->btnFontIn->font();
    writeByStream(font);
}


void MainWindow::on_btnColorIn_clicked()
{
    QPalette plet = ui->btnColorIn->palette();
    QColor color = plet.buttonText().color();
    color = QColorDialog::getColor(color);
    if (color.isValid()) {
        plet.setColor(QPalette::ButtonText, color);
        ui->btnColorIn->setPalette(plet);
    }
}

void MainWindow::on_btnColorWrite_clicked()
{
    QPalette plet = ui->btnColorIn->palette();
    QColor color = plet.buttonText().color();
    writeByStream(color);
}




void MainWindow::on_btnInt8Read_clicked()
{
    qint8 value = 0;
    readByStream(value);
    ui->editInt8Out->setText(QString("%1").arg(value));
}


void MainWindow::on_btnUint8Read_clicked()
{
    quint8 value = 0;
    readByStream(value);
    ui->editUint8Out->setText(QString("%1").arg(value));
}


void MainWindow::on_btnInt16Read_clicked()
{
    qint16 value = 0;
    readByStream(value);
    ui->editInt16Out->setText(QString("%1").arg(value));
}


void MainWindow::on_btnUint16Read_clicked()
{
    quint16 value = 0;
    readByStream(value);
    ui->editUint16Out->setText(QString("%1").arg(value));
}


void MainWindow::on_btnInt32Read_clicked()
{
    qint32 value = 0;
    readByStream(value);
    ui->editInt32Out->setText(QString("%1").arg(value));
}


void MainWindow::on_btnInt64Read_clicked()
{
    qint64 value = 0;
    readByStream(value);
    ui->editInt64Out->setText(QString("%1").arg(value));
}


void MainWindow::on_btnBoolRead_clicked()
{
    bool value = false;
    readByStream(value);
    ui->chkBoolOut->setChecked(value);
}


void MainWindow::on_btnFloat16Read_clicked()
{
    qfloat16 value = 0;
    readByStream(value);
    ui->editFloat16Out->setText(QString::asprintf("%.2f", value));
}


void MainWindow::on_btnFloatRead_clicked()
{
    float value = 0;
    readByStream(value);
    ui->editFloatOut->setText(QString::asprintf("%.4f", value));
}


void MainWindow::on_btnDoubleRead_clicked()
{
    double value = 0;
    readByStream(value);
    ui->editDoubleOut->setText(QString::asprintf("%.4f", value));
}


void MainWindow::on_btnStrRead_clicked()
{
    char *value;
    readByStream(value);
    QString str(value);
    ui->editStrOut->setText(str);
}


void MainWindow::on_btnQStrRead_clicked()
{
    QString str;
    readByStream(str);
    ui->editQStrOut->setText(str);
}


void MainWindow::on_btnFontRead_clicked()
{
    QFont font;
    readByStream(font);
    ui->editFontOut->setFont(font);
}


void MainWindow::on_btnColorRead_clicked()
{
    QColor color = Qt::black;
    readByStream(color);
    QPalette plet = ui->editColorOut->palette();
    plet.setColor(QPalette::Text, color);
    ui->editColorOut->setPalette(plet);
}


void MainWindow::on_actionEditClear_triggered()
{

}


void MainWindow::on_actionWriteCon_triggered()
{
    QFile file_dev(filename_);
    if (!file_dev.open(QIODevice::WriteOnly))
        return;

    QDataStream file_strm(&file_dev);
    file_strm.setVersion(QDataStream::Qt_6_2);     //读写版本必须兼容
    if (ui->rBtnLE->isChecked())
        file_strm.setByteOrder(QDataStream::LittleEndian);
    else
        file_strm.setByteOrder(QDataStream::BigEndian);

    if (ui->rBtnSingle->isChecked())
        file_strm.setFloatingPointPrecision(QDataStream::SinglePrecision);
    else
        file_strm.setFloatingPointPrecision(QDataStream::DoublePrecision);

    qint8 value = ui->spinInt8->value();
    file_strm << value;

    quint8 v = ui->spinUint8->value();
    file_strm << v;

    //... 连续写入不同类型的值

    file_dev.close();
    QMessageBox::information(this, "消息", "数据连续写入文件完成");
}


void MainWindow::on_actionReadCon_triggered()
{
    if (!QFile::exists(filename_)) {
        QMessageBox::critical(this, "错误", "文件不存在，文件名：\n" + filename_);
        return;
    }
    QFile file_dev(filename_);
    if (!file_dev.open(QIODevice::ReadOnly))
        return;

    QDataStream file_strm(&file_dev);
    file_strm.setVersion(QDataStream::Qt_6_2);     //读写版本必须兼容
    if (ui->rBtnLE->isChecked())
        file_strm.setByteOrder(QDataStream::LittleEndian);
    else
        file_strm.setByteOrder(QDataStream::BigEndian);

    if (ui->rBtnSingle->isChecked())
        file_strm.setFloatingPointPrecision(QDataStream::SinglePrecision);
    else
        file_strm.setFloatingPointPrecision(QDataStream::DoublePrecision);

    qint8 value = 0;
    file_strm >> value;
    ui->editInt8Out->setText(QString("%1").arg(value));

    quint8 v = 0;
    file_strm >> v;
    ui->editUint8Out->setText(QString("%1").arg(v));

    file_strm.startTransaction();

     //... 连续读取不同类型的值

    if (file_strm.commitTransaction())
        QMessageBox::information(this, "消息", "从文件连续读取数据完成");
    else
        QMessageBox::critical(this, "错误", "文件读取过程出错，请检查文件格式");

    file_dev.close();
}


#include "dialog.h"
#include "ui_dialog.h"

#include <QDir>
#include <QFileDialog>
#include <QPalette>
#include <QColor>
#include <QColorDialog>
#include <QFontDialog>
#include <QFont>
#include <QProgressDialog>
#include <QElapsedTimer>
#include <QLineEdit>
#include <QInputDialog>
#include <QStringList>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_btnClearText_clicked()
{
    ui->plainTextEdit->clear();
}


void Dialog::on_btnOpenFile_clicked()
{
    QString cur_path = QDir::currentPath();
    QString dlg_title = "打卡一个文件";
    QString filter = "文本文件(*.txt);;图片文件(*.jpg *.gif *.png);;所有文件(*.*)";
    QString filename = QFileDialog::getOpenFileName(this, dlg_title, cur_path, filter);
    if (!filename.isEmpty())
        ui->plainTextEdit->appendPlainText(filename);
}


void Dialog::on_btnOpenFiles_clicked()
{
    QString cur_path = QDir::currentPath();
    QString dlg_title = "打卡多个文件";
    QString filter = "文本文件(*.txt);;图片文件(*.jpg *.gif *.png);;所有文件(*.*)";
    QStringList filelist = QFileDialog::getOpenFileNames(this, dlg_title, cur_path, filter);
    for(int i = 0; i < filelist.count(); i++)
        ui->plainTextEdit->appendPlainText(filelist.at(i));
}


void Dialog::on_btnSaveFile_clicked()
{
    QString cur_path = QDir::currentPath();
    QString dlg_title = "保存文件";
    QString filter = "文本文件(*.txt);;图片文件(*.jpg *.gif *.png);;所有文件(*.*)";
    QString filename = QFileDialog::getSaveFileName(this, dlg_title, cur_path, filter);
    if (!filename.isEmpty())
        ui->plainTextEdit->appendPlainText(filename);
}


void Dialog::on_btnSelectExistDir_clicked()
{
    QString cur_path = QDir::currentPath();
    QString dlg_title = "选择已有目录";
    QString selected_dir = QFileDialog::getExistingDirectory(this, dlg_title, cur_path);
    if (!selected_dir.isEmpty())
        ui->plainTextEdit->appendPlainText(selected_dir);
}


void Dialog::on_btnGetColor_clicked()
{
    QPalette pal = ui->plainTextEdit->palette();
    QColor ini_color = pal.color(QPalette::Text);
    QColor color = QColorDialog::getColor(ini_color, this, "选择颜色");
    if (color.isValid()) {
        pal.setColor(QPalette::Text, color);
        ui->plainTextEdit->setPalette(pal);
    }
}


void Dialog::on_btnGetFont_clicked()
{
    QFont ini_font = ui->plainTextEdit->font();
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, ini_font);
    if (ok)
        ui->plainTextEdit->setFont(font);
}


void Dialog::on_progress_canceled() {
    ui->plainTextEdit->appendPlainText("进度条被取消了");
}


void Dialog::on_btnProgress_clicked()
{
    QString lab_text = "正在复制文件...";
    QString btn_text = "取消";
    int minv = 0, maxv = 200;
    QProgressDialog dlg_progress(lab_text, btn_text, minv, maxv, this);
    connect(&dlg_progress, SIGNAL(canceled()), this, SLOT(on_progress_canceled()));
    dlg_progress.setWindowTitle("复制文件");
    dlg_progress.setWindowModality(Qt::WindowModal);        // 以模态方式显示对话框
    dlg_progress.setAutoReset(true);
    dlg_progress.setAutoClose(true);

    // 用循环表示操作进度
    QElapsedTimer ms_counter;
    for (int i = minv; i <= maxv; i++) {
        dlg_progress.setValue(i);
        dlg_progress.setLabelText(QString::asprintf("正在复制第 %d 个文件", i));

        ms_counter.start();
        while (true)
            if (ms_counter.elapsed() > 30)
                break;
        // 中途退出
        if (dlg_progress.wasCanceled())
            break;
    }
}


void Dialog::on_btnInputStr_clicked()
{
    QString title = "输入文字对话框";
    QString lab_txt = "请输入文件名";
    QString ini_txt = "新建文件名.txt";
    QLineEdit::EchoMode echo_mode = QLineEdit::Normal;
    bool ok = false;
    QString txt = QInputDialog::getText(this, title, lab_txt, echo_mode, ini_txt, &ok);
    if (ok && !txt.isEmpty())
        ui->plainTextEdit->appendPlainText(txt);
}


void Dialog::on_btnInputInt_clicked()
{
    QString title = "输入整数对话框";
    QString lab_txt = "设置文本框字体大小";
    int default_val = ui->plainTextEdit->font().pointSize();   // 现有字体大小
    int minv = 6, maxv = 50, stepv = 1;
    bool ok = false;
    int input_val = QInputDialog::getInt(this, title, lab_txt, default_val, \
                                         minv, maxv, stepv, &ok);
    if (ok) {
        ui->plainTextEdit->appendPlainText(QString("文本框字体大小被设置为：%1").arg(input_val));
        QFont font = ui->plainTextEdit->font();
        font.setPointSize(input_val);
        ui->plainTextEdit->setFont(font);
    }
}


void Dialog::on_btnInputItem_clicked()
{
    QStringList items;
    items << "优秀" << "良好" << "合格" << "不合格";
    QString title = "条目选择对话框";
    QString lab_txt = "请选择级别";
    int cur_index = 0;
    bool editable = true;
    bool ok = false;
    QString item = QInputDialog::getItem(this, title, lab_txt, items, cur_index, editable, &ok);
    if (ok && !item.isEmpty()) {
        ui->plainTextEdit->appendPlainText(QString("选择了条目：%1").arg(item));
    }
}


void Dialog::on_btnInputFloat_clicked()
{
    QString title = "输入浮点数对话框";
    QString lab_txt = "请输入一个浮点数";
    float default_val = 3.14;   // 现有字体大小
    float minv = 0, maxv = 10000;
    int decmals        = 3;     // 小数点位数
    bool ok = false;
    float input_val = QInputDialog::getDouble(this, title, lab_txt, default_val, \
                                         minv, maxv, decmals, &ok);
    if (ok) {
        ui->plainTextEdit->appendPlainText(QString("输入了一个浮点数：%1").arg(input_val));
    }
}


void Dialog::on_btnWarn_clicked()
{
    QString title = "warning 消息对话框";
    QString str = "文件内容已被修改";
    QMessageBox::warning(this, title, str);
}


void Dialog::on_btnCritical_clicked()
{
    QString title = "critical 消息对话框";
    QString str = "有不明程序访问网络";
    QMessageBox::critical(this, title, str);
}


void Dialog::on_btnAbout_clicked()
{
    QString title = "about 消息对话框";
    QString str = "SEGY 文件查看软件 V1.0 \nDesigned by wwb";
    QMessageBox::about(this, title, str);
}


void Dialog::on_btnAboutQt_clicked()
{
    QString title = "about Qt 消息对话框";
    QMessageBox::aboutQt(this, title);
}


void Dialog::on_btnInfo_clicked()
{
    QString title = "information 消息对话框";
    QString str = "文件已打开，请检查";
    QMessageBox::information(this, title, str);
}


void Dialog::on_btnQues_clicked()
{
    QString title = "question 消息对话框";
    QString str = "文件已修改，是否保存";
    QMessageBox::StandardButton default_btn = QMessageBox::NoButton;    // 默认按钮
    QMessageBox::StandardButton result;     // 返回按钮的选择

    result = QMessageBox::question(this, title, str, \
                                   QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,\
                                   default_btn);
    if (result == QMessageBox::Yes)
        ui->plainTextEdit->appendPlainText("选择了 yes");
    else if (result == QMessageBox::No)
        ui->plainTextEdit->appendPlainText("选择了 No");
    else if (result == QMessageBox::Cancel)
        ui->plainTextEdit->appendPlainText("选择了 cancel");
    else
        ui->plainTextEdit->appendPlainText("无选择");
}


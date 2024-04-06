#include "dialoglogin.h"
#include "ui_dialoglogin.h"

#include <QLineEdit>
#include <QSettings>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QMouseEvent>

DialogLogin::DialogLogin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogLogin)
{
    ui->setupUi(this);
    ui->lineEditPasswd->setEchoMode(QLineEdit::Password);   // 设置为密码模式输入
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::SplashScreen);     // 窗口无边框，不在任务栏显示
    QApplication::setOrganizationName("WWB-Qt");    // 设置组织名
    QApplication::setApplicationName("sample7-05"); // 设置应用程序名
    readSettings();
}

DialogLogin::~DialogLogin()
{
    delete ui;
}

void DialogLogin::readSettings() {
    QSettings settings;
    bool saved = settings.value("saved", false).toBool();
    user_ = settings.value("Username", "user").toString();
    QString default_pswd = encrypt("12345");
    pswd_ = settings.value("PSWD", default_pswd).toString();
    if (saved)
        ui->lineEditUsername->setText(user_);
    ui->chkSaveUsername->setChecked(saved);
}


void DialogLogin::writeSettings(){
    QSettings settings;
    settings.setValue("Username", user_);
    settings.setValue("PSWD", pswd_);
    settings.setValue("saved", ui->chkSaveUsername->isChecked());
}

QString DialogLogin::encrypt(const QString &str){
    QByteArray bt_array = str.toLocal8Bit();
    QCryptographicHash hash(QCryptographicHash::Md5);   // 使用md5算法加密
    hash.addData(bt_array);                             // 添加数据到加密哈希值
    QByteArray result_array = hash.result();            // 返回最终的哈希值
    QString md5 = result_array.toHex();
    return md5;
}

void DialogLogin::on_btnOK_clicked()
{
    QString user = ui->lineEditUsername->text().trimmed();
    QString pswd = ui->lineEditPasswd->text().trimmed();
    QString encrpt_pswd = encrypt(pswd);
    if (user == user_ && encrpt_pswd == pswd_) {
        writeSettings();
        this->accept();
    } else {
        try_count_++;
        if (try_count_ > 3) {
            QMessageBox::critical(this, "错误", "输入次数太多，强行退出");
            this->reject();
        } else
            QMessageBox::warning(this, "错误提示", "用户名或密码错误");
    }
}


// void DialogLogin::mousePressEvent(QMouseEvent *event){
//     if(event->button() == Qt::LeftButton) {
//         moving_ = true;
//         last_pos_ = event->globalPosition().toPoint() - this->pos();
//     }
//     qDebug("mouse pressed");
//     return QDialog::mousePressEvent(event);
// }

// void DialogLogin::mouseMoveEvent(QMouseEvent *event){
//     QPoint event_pos = event->globalPosition().toPoint();
//     if (moving_ && (event->buttons() & Qt::LeftButton) \
//         && (event_pos - last_pos_).manhattanLength() > QApplication::startDragDistance()) {

//         QPoint dis = event_pos - last_pos_;
//         move(dis);
//         last_pos_ = event_pos - this->pos();
//         qDebug("dis.x=%d, dis.y=%d, last_pos_.x=%d, last_pos_.y=%d", dis.x(), dis.y(), last_pos_.x(), \
//                          last_pos_.y());
//         qDebug("mouse moving, startDragDistance = %d", QApplication::startDragDistance());
//     }

//     return QDialog::mouseMoveEvent(event);
// }
void DialogLogin::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton) {
        moving_ = true;
        last_global_pos_ = event->globalPosition().toPoint();
    }
    qDebug("mouse pressed");
    return QDialog::mousePressEvent(event);
}

void DialogLogin::mouseMoveEvent(QMouseEvent *event){
    QPoint event_pos = event->globalPosition().toPoint();

    if (moving_ && (event->buttons() & Qt::LeftButton) \
        && (event_pos - last_global_pos_).manhattanLength() > QApplication::startDragDistance()) {

        move(this->pos() + (event_pos - last_global_pos_));
        last_global_pos_ = event_pos;
        qDebug("mouse moving, startDragDistance = %d", QApplication::startDragDistance());
    }

    return QDialog::mouseMoveEvent(event);
}
void DialogLogin::mouseReleaseEvent(QMouseEvent *event){
    moving_ = false;         // 停止移动
    qDebug("mouse released");
    event->accept();
}


#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>

namespace Ui {
class DialogLogin;
}

class DialogLogin : public QDialog
{
    Q_OBJECT
private:
    QPoint last_global_pos_;
    bool moving_ = false;       // 表示窗口是否在鼠标操作下移动
    QPoint last_pos_;           // 上一次鼠标光标的位置
    QString user_ = "user";     // 初始用户名
    QString pswd_ = "12345";    // 初始密码
    int try_count_ = 0;         // 试错次数

    void readSettings();        // 读取设置
    void writeSettings();       // 写入设置
    QString encrypt(const QString &str);        // 字符串加密

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public:
    explicit DialogLogin(QWidget *parent = nullptr);
    ~DialogLogin();

private slots:
    void on_btnOK_clicked();

private:
    Ui::DialogLogin *ui;
};

#endif // DIALOGLOGIN_H

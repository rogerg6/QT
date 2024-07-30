#ifndef TPENDIALOG_H
#define TPENDIALOG_H


#include    <QDialog>
#include    <QPen>
#include "SharedLib_global.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TPenDialog; }
QT_END_NAMESPACE

//QPen属性设置对话框
/**
 * @brief SHAREDLIB_EXPORT被解析为Q_DECL_EXPORT，因为在pro文件中定义了SHAREDLIB_LIBRARY
 *        代表导出TPenDialog类给别的app使用
 */
class SHAREDLIB_EXPORT TPenDialog : public QDialog
{
    Q_OBJECT
private:
    QPen  m_pen;  //成员变量
public:
    TPenDialog(QWidget *parent = nullptr);
    ~TPenDialog();

    void    setPen(QPen &pen);  //设置QPen对象，用于对话框的界面显示
    QPen    getPen();           //获取对话框设置的QPen的属性
    static  QPen  getPen(QPen  &iniPen, bool *ok);  //静态函数

private slots:
    void on_btnColor_clicked();

private:
    Ui::TPenDialog *ui;
};

#endif // TPENDIALOG_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSpinBox>
#include <QTreeWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    enum TreeItemType {itTopItem=1001, itGroupItem, itImageItem};

    //枚举类型，表示列号
    enum    treeColNum{colItem=0, colItemType=1, colDate}; //目录树列的编号定义

    QLabel *labFileName;
    QLabel *labNodeText;
    QSpinBox *spinRatio;

    QPixmap pixmap_;        // 保存原始图片的副本
    float ratio_;

    void buildTreeHeader();// 构建表头
    void initTree();       // 目录树初始化

    void addFolderItem(QTreeWidgetItem *parItem, QString dirName);      // 添加目录节点
    QString getFinalFolderName(const QString &fullPathName);            // 提取目录名称
    void addImageItem(QTreeWidgetItem *parItem, QString aFileName);     // 添加图片节点
    void displayImage(QTreeWidgetItem *item);                           // 显示图片节点关联的图片
    void changeItemCaption(QTreeWidgetItem *item);                      // 遍历改变节点标题
    void deleteItem(QTreeWidgetItem *parItem, QTreeWidgetItem *item);   // 删除一个节点


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actAddDir_triggered();

    void on_actAddFile_triggered();

    void on_treeFile_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_actDelNode_triggered();

    void on_actScanNode_triggered();

    void on_actZoomIn_triggered();

    void on_actZoomOut_triggered();

    void on_actFitReal_triggered();

    void on_actFitW_triggered();

    void on_actFitH_triggered();

    void on_actFloat_triggered();

    void on_actFloat_triggered(bool checked);

    void on_actVisiable_triggered(bool checked);

    void on_dockWidget_topLevelChanged(bool topLevel);

    void on_dockWidget_visibilityChanged(bool visible);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

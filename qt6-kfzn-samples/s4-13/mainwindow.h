#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    enum CellType {ctName=1000, ctSex, ctBirth, ctNation, ctPartyM, ctScore};
    enum FieldColNum {colName=0, colSex, colBirth, colNation, colPartyM, colScore};
    QLabel *labCellIndex;       // 状态栏上显示单元格的行号、列号
    QLabel *labCellType;        // 状态栏上显示单元格的类型
    QLabel *labStudId;          // 状态栏上显示单元格的数据

    // 为某一行创建items
    void createItemsARow(int rowNo, QString name, QString sex, QDate birth, QString nation, bool isPM, int score);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnSetHeader_clicked();

    void on_btnInitData_clicked();

    void on_tabInfo_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_btnInsertRow_clicked();

    void on_btnAppendRow_clicked();

    void on_btnDelCurRow_clicked();

    void on_btnAutoH_clicked();

    void on_btnAutoW_clicked();

    void on_btnSetRow_clicked();

    void on_chkTabEditable_clicked(bool checked);

    void on_chkRowColor_clicked(bool checked);

    void on_chkShowHeader_clicked(bool checked);

    void on_chkShowHeaderV_clicked(bool checked);

    void on_rBtnSelRow_clicked();

    void on_rBtnSelItem_clicked();

    void on_btnReadTab_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

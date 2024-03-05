#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include    <QSpinBox>
#include    <QFontComboBox>
#include <QActionGroup>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // 状态栏使用
    QLabel *labFile;
    QLabel *labInfo;
    QProgressBar *progBar;

    //
    QActionGroup *act_grp;

    // 工具栏使用
    QSpinBox *spinFontSize;
    QFontComboBox *comboFontName;

    void buildUI();
    void buildSingnalSlots();

private slots:
    void do_fontSize_changed(int fontSize);
    void do_fontSelected(const QFont &font);


    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionColse_triggered();

    void on_actionBold_triggered();

    void on_actionBold_triggered(bool checked);

    void on_actionItalic_triggered(bool checked);

    void on_actionUnderline_triggered(bool checked);

    void on_actionToggleText_triggered(bool checked);

    void on_textEdit_selectionChanged();

    void on_textEdit_copyAvailable(bool b);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

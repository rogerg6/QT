#ifndef DIALOGLOCATE_H
#define DIALOGLOCATE_H

#include <QDialog>

namespace Ui {
class DialogLocate;
}

class DialogLocate : public QDialog
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);

public:
    explicit DialogLocate(QWidget *parent = nullptr);
    ~DialogLocate();
    void setSpinRange(int row_cnt, int col_cnt);

public slots:
    void setSpinValue(int row_no, int col_no);

private slots:
    void on_btnSetText_clicked();

signals:
    void changeCellText(int row, int col, QString &text);
    void changeActionEnable(bool en);

private:
    Ui::DialogLocate *ui;
};

#endif // DIALOGLOCATE_H

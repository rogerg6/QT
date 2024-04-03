#ifndef FORMDOC_H
#define FORMDOC_H

#include <QWidget>

namespace Ui {
class FormDoc;
}

class FormDoc : public QWidget
{
    Q_OBJECT

public:
    explicit FormDoc(QWidget *parent = nullptr);
    ~FormDoc();
    void loadFromFile(QString &filename);   // 自定义函数

signals:
    void titleChanged(QString title);       // 自定义信号

private slots:
    void on_actOpen_triggered();

    void on_actFont_triggered();

private:
    Ui::FormDoc *ui;
};

#endif // FORMDOC_H

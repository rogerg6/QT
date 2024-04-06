#ifndef FORMDOC_H
#define FORMDOC_H

#include <QWidget>

namespace Ui {
class FormDoc;
}

class FormDoc : public QWidget
{
    Q_OBJECT
private:
    QString filename_;              // 当前文件
    bool file_opened_ = false;      // 文件已打开

public:
    explicit FormDoc(QWidget *parent = nullptr);
    ~FormDoc();

    void loadFromFile(QString &filename);
    void saveToFile();
    QString currentFileName();
    bool isFileOpened();
    void setEditFont();
    void textCut();
    void textCopy();
    void textPaste();

private:
    Ui::FormDoc *ui;
};

#endif // FORMDOC_H

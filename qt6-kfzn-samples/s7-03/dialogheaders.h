#ifndef DIALOGHEADERS_H
#define DIALOGHEADERS_H

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class DialogHeaders;
}

class DialogHeaders : public QDialog
{
    Q_OBJECT
private:
    QStringListModel *model_;

public:
    explicit DialogHeaders(QWidget *parent = nullptr);
    ~DialogHeaders();

    void setHeaderList(QStringList &header);
    QStringList headerList();

private:
    Ui::DialogHeaders *ui;
};

#endif // DIALOGHEADERS_H

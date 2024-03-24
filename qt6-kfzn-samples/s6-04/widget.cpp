#include "widget.h"
#include "ui_widget.h"

#include <QMimeData>
#include <QFileInfo>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->lab->setScaledContents(true);
    this->setAcceptDrops(true);

    // 不接受放置，由窗口处理
    ui->lab->setAcceptDrops(false);
    ui->plainTextEdit->setAcceptDrops(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::dragEnterEvent(QDragEnterEvent *event){
    // 显示mime数据
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText("dragEnterEvent 事件 mimeData()->formats");
    for (int i = 0; i < event->mimeData()->formats().size(); i++)
        ui->plainTextEdit->appendPlainText(event->mimeData()->formats().at(i));

    // 显示路径名
    ui->plainTextEdit->appendPlainText("\n dragEnterEvent 事件 mimeData()->urls()");
    for (int i = 0; i < event->mimeData()->urls().size(); i++){
        QUrl url = event->mimeData()->urls().at(i);
        ui->plainTextEdit->appendPlainText(url.path());
    }

    // 处理事件
    if (event->mimeData()->hasUrls()) {
        QString filename = event->mimeData()->urls().at(0).fileName();
        QFileInfo fileinfo(filename);
        QString ext = fileinfo.suffix().toUpper();
        if (ext == "JPG")           // 只接受jpg拖放
            event->acceptProposedAction();
        else
            event->ignore();
    } else {
        event->ignore();
    }
}


void Widget::resizeEvent(QResizeEvent *event) {
    QSize sz = ui->plainTextEdit->size();
    ui->plainTextEdit->resize(this->width()-10, sz.height());
    ui->lab->resize(this->width()-10, this->height()-sz.height()-20);
    event->accept();
}


void Widget::dropEvent(QDropEvent *event) {
    QString filename = event->mimeData()->urls().at(0).path();
    filename = filename.right(filename.length() - 1);
    QPixmap pix(filename);
    ui->lab->setPixmap(pix);
    event->accept();
}

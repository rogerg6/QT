#include "formdoc.h"
#include "ui_formdoc.h"

#include <QToolBar>
#include <QVBoxLayout>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QFont>
#include <QFontDialog>


FormDoc::FormDoc(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormDoc)
{
    ui->setupUi(this);

    /* 代码创建工具栏，因为自定义类型ui在Qt Designer中
     * 无法创建工具栏
     */
    QToolBar *loc_tool_bar = new QToolBar("文档", this);
    loc_tool_bar->addAction(ui->actOpen);
    loc_tool_bar->addAction(ui->actFont);
    loc_tool_bar->addSeparator();
    loc_tool_bar->addAction(ui->actCut);
    loc_tool_bar->addAction(ui->actCopy);
    loc_tool_bar->addAction(ui->actPaste);
    loc_tool_bar->addAction(ui->actUndo);
    loc_tool_bar->addAction(ui->actRedo);
    loc_tool_bar->addSeparator();
    loc_tool_bar->addAction(ui->actClose);
    loc_tool_bar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    // 设计布局
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(loc_tool_bar);
    layout->addWidget(ui->plainTextEdit);
    layout->setContentsMargins(2,2,2,2);
    layout->setSpacing(2);
    this->setLayout(layout);
}

FormDoc::~FormDoc()
{
    delete ui;
}

void FormDoc::loadFromFile(QString &filename) {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream strm(&file);
        ui->plainTextEdit->clear();
        while (!strm.atEnd()) {
            QString str = strm.readLine();
            ui->plainTextEdit->appendPlainText(str);
        }
        file.close();

        QFileInfo fileinfo(filename);
        QString shortname = fileinfo.fileName();
        this->setWindowTitle(shortname);
        emit titleChanged(shortname);           // 发射信号
    }
}

void FormDoc::on_actOpen_triggered()
{
    QString curpath = QDir::currentPath();
    QString filename = QFileDialog::getOpenFileName(this, "打开一个文件", curpath,\
                         "C程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)");
    if (filename.isEmpty())
        return;
    loadFromFile(filename);
}


void FormDoc::on_actFont_triggered()
{
    QFont font = ui->plainTextEdit->font();
    bool ok;
    font = QFontDialog::getFont(&ok, font);
    ui->plainTextEdit->setFont(font);
}


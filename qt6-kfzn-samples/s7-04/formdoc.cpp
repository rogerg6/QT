#include "formdoc.h"
#include "ui_formdoc.h"

#include <QFontDialog>
#include <QFile>
#include <QFileInfo>

FormDoc::FormDoc(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormDoc)
{
    ui->setupUi(this);
    setWindowTitle("New Doc[*]");
    setAttribute(Qt::WA_DeleteOnClose);
    connect(ui->plainTextEdit, &QPlainTextEdit::modificationChanged, this, &QWidget::setWindowModified);
}

FormDoc::~FormDoc()
{
    delete ui;
}

void FormDoc::loadFromFile(QString &filename) {
    QFile f(filename);
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream strm(&f);
        ui->plainTextEdit->clear();
        ui->plainTextEdit->setPlainText(strm.readAll());

        filename_ = filename;
        QFileInfo fi(filename);
        QString str = fi.fileName();
        this->setWindowTitle(str + "[*]");
        file_opened_ = true;
    }
}

void FormDoc::saveToFile() {
    // 不执行具体的保存操作
    this->setWindowModified(false);
}

QString FormDoc::currentFileName() {
    return filename_;
}

bool FormDoc::isFileOpened() {
    return file_opened_;
}

void FormDoc::setEditFont() {
    QFont font = ui->plainTextEdit->font();
    bool ok;
    font = QFontDialog::getFont(&ok, font);
    ui->plainTextEdit->setFont(font);
}

void FormDoc::textCut() {
    ui->plainTextEdit->cut();
}

void FormDoc::textCopy(){
    ui->plainTextEdit->copy();
}
void FormDoc::textPaste(){
    ui->plainTextEdit->paste();
}

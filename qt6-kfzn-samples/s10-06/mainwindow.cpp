#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QPixmap>
#include <QMessageBox>
#include <QPrintPreviewDialog>
#include <QTextBlock>
#include <QPrintDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->splitter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showImageFeatures(bool formatChanged) {
    if (formatChanged) { // 格式转换后需要显示全部信息
        QImage::Format fmt = img_.format();
        if (fmt == QImage::Format_RGB32)
            ui->editImgFormat->setText("32-bit RGB(0xffRRGGBB)");
        else if (fmt == QImage::Format_RGB16)
            ui->editImgFormat->setText("16-bit RGB565");
        else if (fmt == QImage::Format_RGB888)
            ui->editImgFormat->setText("24-bit RGB888");
        else if (fmt == QImage::Format_Grayscale8)
            ui->editImgFormat->setText("8-bit grayscale");
        else if (fmt == QImage::Format_Grayscale16)
            ui->editImgFormat->setText("16-bit grayscale");
        else if (fmt == QImage::Format_ARGB32)
            ui->editImgFormat->setText("32-bit ARGB(0xAARRGGBB)");
        else if (fmt == QImage::Format_Indexed8)
            ui->editImgFormat->setText("8-bit indexes into a colormap");
        else
            ui->editImgFormat->setText(QString("Format= %1,其他格式").arg(fmt));

        ui->editImgDepth->setText(QString("%1 bits/pixel").arg(img_.depth()));
        ui->editImgBitPlane->setText(QString("%1 bits").arg(img_.bitPlaneCount()));
        ui->chkHasAlpha->setChecked(img_.hasAlphaChannel());
        ui->chkIsGray->setChecked(img_.isGrayscale());
    }

    // 缩放或旋转后显示大小信息
    ui->editImgHeight->setText(QString("%1 像素").arg(img_.height()));
    ui->editImgWidth->setText(QString("%1 像素").arg(img_.width()));
    qsizetype sz = img_.sizeInBytes();  // 图像数据字节数
    if(sz < 1024 * 9)
        ui->editImgSize->setText(QString("%1 Bytes").arg(sz));
    else
        ui->editImgSize->setText(QString("%1 KB").arg(sz/1024));
    QString dpi = QString::asprintf("DPI_X=%.0f, DPI_Y=%.0f", \
              img_.dotsPerMeterX()*0.0254, img_.dotsPerMeterY()*0.0254);
    ui->editImgDPI->setText(dpi);
}

void MainWindow::imageModified(bool modified){
    ui->actFileReload->setEnabled(modified);
    ui->actFileSave->setEnabled(modified);
}

void MainWindow::printImage(QPainter *painter, QPrinter *printer) {
    QMargins margin(20,40,20,40);   // 上下左右4个边距，单位像素
    QRectF page_rect = printer->pageRect(QPrinter::DevicePixel);
    int pagew = page_rect.width();
    int pageh = page_rect.height();

    const int line_inc = 20;    // 行高， 单位像素
    int curx = margin.left();
    int cury = margin.top();
    painter->drawText(curx, cury, filename_);
    cury += line_inc;

    painter->drawText(curx, cury, QString("Page width=%1 像素").arg(pagew));
    painter->drawText(200, cury, QString("Image width=%1 像素").arg(img_.width()));
    cury += line_inc;
    painter->drawText(curx, cury, QString("Page height=%1 像素").arg(pageh));
    painter->drawText(200, cury, QString("Image height=%1 像素").arg(img_.height()));
    cury += line_inc;

    int spaceh = pageh - cury;      // 页面剩余高度
    // 图像未超出页面剩余空间，则居中打印
    if ((pagew > img_.width()) && (spaceh > img_.height())) {
        curx = (pagew - img_.width()) / 2;
        painter->drawImage(curx, cury, img_);
        return;
    }

    // 如果图像超出页面剩余空间，则缩放打印
    QImage new_img;
    if (img_.height() > img_.width())
        new_img = img_.scaledToHeight(spaceh);
    else
        new_img = img_.scaledToWidth(pagew);
    curx = (pagew - new_img.width()) / 2;   // 水平居中
    painter->drawImage(curx, cury, new_img);
}

void MainWindow::printRGB565Data(QPainter *painter, QPrinter *printer){
    QMargins margin(20,40,20,40);   // 上下左右4个边距，单位像素
    QRectF page_rect = printer->pageRect(QPrinter::DevicePixel);
    int pagew = page_rect.width();
    int pageh = page_rect.height();

    const int line_inc = 20;    // 行高， 单位像素
    int curx = margin.left();
    int cury = margin.top();
    QFont font = ui->plainTextEdit->font();
    painter->setFont(font);
    int page_number=1;

    // 页脚画线
    painter->drawLine(margin.left(), pageh - margin.bottom()+1,
                      pagew - margin.right(), pageh-margin.bottom()+1);
    // 页脚编号
    painter->drawText(pagew-5*margin.right(), pageh-margin.bottom()+20,
                      QString("第%1页").arg(page_number));

    QTextDocument *doc = ui->plainTextEdit->document(); // 文本对象
    int cnt = doc->blockCount();    // 回车符是一个块
    for (int i = 0; i < cnt; i++) {
        QTextBlock text_line = doc->findBlockByLineNumber(i);
        QString str = text_line.text();
        painter->drawText(curx, cury, str);

        cury += line_inc;
        if (cury >= (pageh - margin.bottom())) {
            printer->newPage();
            cury = margin.top();
            page_number++;
            // 页脚画线
            painter->drawLine(margin.left(), pageh - margin.bottom()+1,
                              pagew - margin.right(), pageh-margin.bottom()+1);
            // 页脚编号
            painter->drawText(pagew-5*margin.right(), pageh-margin.bottom()+20,
                              QString("第%1页").arg(page_number));
        }
    }

}

void MainWindow::do_paintRequestedImage(QPrinter *printer){
    QPainter painter(printer);
    printImage(&painter, printer);
}

void MainWindow::do_paintRequestedText(QPrinter *printer){
    QPainter painter(printer);
    printRGB565Data(&painter, printer);
}

void MainWindow::on_actFileOpen_triggered()
{
    QString cur_path = QDir::currentPath();
    QString filter = "图片文件(*.bmp *.jpg *.png);;"
                     "BMP文件(*.bmp);;JPG文件(*.jpg);;PNG文件(*.png)";
    QString fname = QFileDialog::getOpenFileName(this, "选择图片文件", cur_path, filter);
    if (fname.isEmpty())
        return;

    ui->statusbar->showMessage(fname);
    filename_ = fname;
    QFileInfo fileinfo(filename_);
    QDir::setCurrent(fileinfo.absolutePath());

    img_.load(filename_);
    QPixmap pixmap = QPixmap::fromImage(img_);  // 创建QPixmap用于界面显示
    ui->labPic->setPixmap(pixmap);
    ui->tabWidget->setCurrentIndex(0);
    showImageFeatures();

    ui->actFileSaveAs->setEnabled(true);
    ui->actFilePreview->setEnabled(true);
    ui->actFilePrint->setEnabled(true);
    ui->actImgZoomIn->setEnabled(true);
    ui->actImgZoomOut->setEnabled(true);
    ui->actImgRotateLeft->setEnabled(true);
    ui->actImgRotateRight->setEnabled(true);
    ui->actImgFlipUD->setEnabled(true);
    ui->actImgFlipLR->setEnabled(true);
}


void MainWindow::on_actFileSave_triggered()
{
    img_.save(filename_);
    imageModified(false);
}


void MainWindow::on_actFileSaveAs_triggered()
{
    QString filter = "图片文件(*.bmp *.jpg *.png);;"
                     "BMP文件(*.bmp);;JPG文件(*.jpg);;PNG文件(*.png)";
    QString fname = QFileDialog::getSaveFileName(this, "保存文件", filename_, filter);
    if (fname.isEmpty())
        return;

    img_.save(fname);       // 保存为新文件
    filename_ = fname;
    ui->statusbar->showMessage(fname);
    imageModified(false);
}


void MainWindow::on_actFileReload_triggered()
{
    QString fname = filename_;
    img_.load(fname);
    QPixmap pixmap = QPixmap::fromImage(img_);  // 创建QPixmap用于界面显示
    ui->labPic->setPixmap(pixmap);
    ui->tabWidget->setCurrentIndex(0);
    showImageFeatures(true);
    imageModified(false);
}


void MainWindow::on_btnImgFormatConvert_clicked()
{
    int index = ui->comboFormat->currentIndex();
    if (index == 0)
        img_.convertTo(QImage::Format_RGB16);
    else if (index == 1)
        img_.convertTo(QImage::Format_RGB888);
    else if (index == 2)
        img_.convertTo(QImage::Format_RGB32);
    else if (index == 3)
        img_.convertTo(QImage::Format_Grayscale8);
    else if (index == 4)
        img_.convertTo(QImage::Format_Grayscale16);
    else if (index == 5)
        img_.convertTo(QImage::Format_Indexed8);
    else
        return;

    QPixmap pixmap = QPixmap::fromImage(img_);  // 创建QPixmap用于界面显示
    ui->labPic->setPixmap(pixmap);
    showImageFeatures(true);
    imageModified(true);
}


void MainWindow::on_actImgZoomIn_triggered()
{
    int w = img_.width();
    int h = img_.height();
    img_ = img_.scaled(1.1*w, 1.1*h, Qt::KeepAspectRatio);
    QPixmap pixmap = QPixmap::fromImage(img_);  // 创建QPixmap用于界面显示
    ui->labPic->setPixmap(pixmap);
    showImageFeatures(true);
    imageModified(true);
}


void MainWindow::on_actImgZoomOut_triggered()
{
    int w = img_.width();
    int h = img_.height();
    img_ = img_.scaled(0.9*w, 0.9*h, Qt::KeepAspectRatio);
    QPixmap pixmap = QPixmap::fromImage(img_);  // 创建QPixmap用于界面显示
    ui->labPic->setPixmap(pixmap);
    showImageFeatures(true);
    imageModified(true);
}


void MainWindow::on_actImgRotateLeft_triggered()
{
    QTransform matrix;
    matrix.reset();     // 单位矩阵
    matrix.rotate(-90); // 默认Qt::ZAxis
    img_ = img_.transformed(matrix);        // 使用变换矩阵matrix进行图像变换
    QPixmap pixmap = QPixmap::fromImage(img_);  // 创建QPixmap用于界面显示
    ui->labPic->setPixmap(pixmap);
    showImageFeatures(true);
    imageModified(true);
}


void MainWindow::on_actImgRotateRight_triggered()
{
    QTransform matrix;
    matrix.reset();     // 单位矩阵
    matrix.rotate(90); // 默认Qt::ZAxis
    img_ = img_.transformed(matrix);        // 使用变换矩阵matrix进行图像变换
    QPixmap pixmap = QPixmap::fromImage(img_);  // 创建QPixmap用于界面显示
    ui->labPic->setPixmap(pixmap);
    showImageFeatures(true);
    imageModified(true);
}


void MainWindow::on_actImgFlipUD_triggered()
{
    bool horizontal = false;
    bool vertical = true;
    img_.mirror(horizontal, vertical);
    QPixmap pixmap = QPixmap::fromImage(img_);  // 创建QPixmap用于界面显示
    ui->labPic->setPixmap(pixmap);
    imageModified(true);
}


void MainWindow::on_actImgFlipLR_triggered()
{
    bool horizontal = true;
    bool vertical = false;
    img_.mirror(horizontal, vertical);
    QPixmap pixmap = QPixmap::fromImage(img_);  // 创建QPixmap用于界面显示
    ui->labPic->setPixmap(pixmap);
    imageModified(true);
}


void MainWindow::on_btnGetRGB565_clicked()
{
    ui->plainTextEdit->clear();
    int w = img_.width();
    int h = img_.height();
    int total = 2 * w * h;  // 总字节数
    QFileInfo fileinfo(filename_);
    QString array_name = fileinfo.baseName();   // 不带后缀的文件名
    QString aline = QString("const unsigned char RGB565_%1[%2] = {").arg(array_name).arg(total);
    ui->plainTextEdit->appendPlainText(aline);

    QString one_pixel;
    QChar ch0('0');
    int base = 16;
    int count = 0;
    for(int y = 0; y < h; y++) {
        QApplication::processEvents();
        for (int x = 0; x < w; x++) {
            QRgb rgb = img_.pixel(x,y);
            quint16 red = qRed(rgb) & 0x00F8;       // 取高5位
            quint16 green = qGreen(rgb) & 0x00FC;   // 取高6位
            quint16 blue = qBlue(rgb) & 0x00F8;     // 取高5位
            quint16 rgb565 = (red<<8) | (green<<3) | (blue>>3);     // RGB565数据
            quint8 byte_lsb = rgb565 & 0x00FF;  // 低字节
            quint8 byte_msb = rgb565 >>8;       // 高字节

            if (ui->radioLSB->isChecked())
                one_pixel += QString("0x%1,0x%2,").arg(byte_lsb, 2, base, ch0)
                                 .arg(byte_msb, 2, base, ch0);
            else
                one_pixel += QString("0x%1,0x%2,").arg(byte_msb, 2, base, ch0)
                                 .arg(byte_lsb, 2, base, ch0);

            count++;
            if (count == 8) {
                one_pixel = one_pixel.toUpper();
                one_pixel = one_pixel.replace(QChar('X'), "x");
                ui->plainTextEdit->appendPlainText(one_pixel);
                one_pixel = "";
                count = 0;
            }
        }
    }

    if (count > 0) {
        one_pixel = one_pixel.toUpper();
        one_pixel = one_pixel.replace(QChar('X'), "x");
        ui->plainTextEdit->appendPlainText(one_pixel);
    }
    ui->plainTextEdit->appendPlainText("};");
    ui->tabWidget->setCurrentIndex(1);
    ui->btnSaveAsDataFile->setEnabled(true);
    QMessageBox::information(this, "提示", "RGB565数据生成已完成");
}


void MainWindow::on_btnSaveAsDataFile_clicked()
{
    QFileInfo file_info(filename_);
    QString new_name = file_info.baseName() + ".h";
    QString filter = "C语言头文件(*.h);;C语言程序文件(*.c);;文本文件(*.txt)";

    QString file_name = QFileDialog::getSaveFileName(this, "保存文件", new_name, filter);
    if (file_name.isEmpty())
        return;

    QFile file(file_name);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QString str = ui->plainTextEdit->toPlainText();
        QByteArray str_bytes = str.toUtf8();
        file.write(str_bytes, str_bytes.length());
        file.close();
    }
}


void MainWindow::on_actFilePreview_triggered()
{
    QPrintPreviewDialog prev_dlg(this);
    prev_dlg.setWindowFlag(Qt::WindowMaximizeButtonHint);   // 具有最大化的按钮
    if (ui->tabWidget->currentIndex() == 0)
        connect(&prev_dlg, SIGNAL(paintRequested(QPrinter*)),
                this, SLOT(do_paintRequestedImage(QPrinter*)));
    else
        connect(&prev_dlg, SIGNAL(paintRequested(QPrinter*)),
                this, SLOT(do_paintRequestedText(QPrinter*)));
    prev_dlg.exec();    // 已模态方式显示窗口
}


void MainWindow::on_actFilePrint_triggered()
{
    QPrinter printer;
    QPrintDialog printdlg(&printer, this);
    if (printdlg.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        if (ui->tabWidget->currentIndex() == 0)
            printImage(&painter, &printer);
        else
            printRGB565Data(&painter, &printer);
    }
}


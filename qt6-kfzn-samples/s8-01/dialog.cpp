#include "dialog.h"
#include "ui_dialog.h"

#include <QFileInfo>
#include <QDir>
#include <QTemporaryDir>
#include <QTemporaryFile>
#include <QFileSystemWatcher>
#include <QFileDialog>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Window);    // 使窗口具有最大化，最小化按钮
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::do_directoryChanged(const QString &path){
    ui->plainTextEdit->appendPlainText(path + "目录发生了变化\n");
}

void Dialog::do_fileChanged(const QString &path){
    ui->plainTextEdit->appendPlainText(path + "文件发生了变化\n");
}


void Dialog::showBtnInfo(QObject *btn) {
    QPushButton *theBtn = static_cast<QPushButton*>(btn);
    ui->plainTextEdit->appendPlainText("Button: " + theBtn->text());
    ui->plainTextEdit->appendPlainText("Tooltip: " + theBtn->toolTip());
}


///////////////////////// QCoreApplication //////////////////////////////////
// QCoreApplication::applicationName
void Dialog::on_pushButton_3_clicked()
{
    showBtnInfo(sender());
    QCoreApplication::setApplicationName("My app");
    QString str = QCoreApplication::applicationName();
    ui->plainTextEdit->appendPlainText("applicationName: " + str+"\n");
}

// QCoreApplication::organizationName
void Dialog::on_pushButton_6_clicked()
{
    showBtnInfo(sender());
    QCoreApplication::setOrganizationName("UPC");
    QString str = QCoreApplication::organizationName();
    ui->plainTextEdit->appendPlainText("organizationName: " + str+"\n");
}

// QCoreApplication::applicationDirPath()
void Dialog::on_pushButton_clicked()
{
    showBtnInfo(sender());
    ui->plainTextEdit->appendPlainText("应用程序可执行文件所在路径：" \
                                       + QCoreApplication::applicationDirPath());
}

// QCoreApplication::applicationFilePath()
void Dialog::on_pushButton_2_clicked()
{
    showBtnInfo(sender());
    ui->plainTextEdit->appendPlainText("应用程序带有路径的完整文件名：" \
          + QCoreApplication::applicationDirPath());
}

// QCoreApplication::setApplicationName()
void Dialog::on_pushButton_4_clicked()
{
    showBtnInfo(sender());
    QCoreApplication::setApplicationName("Sample 8-01");
}

// QCoreApplication::libraryPaths()
void Dialog::on_pushButton_5_clicked()
{
    showBtnInfo(sender());
    QStringList libs = QCoreApplication::libraryPaths();
    ui->plainTextEdit->appendPlainText("应用程序动态加载库文件时搜索的目录：");
    for (int i = 0; i < libs.size(); i++)
        ui->plainTextEdit->appendPlainText(libs.at(i));
    ui->plainTextEdit->appendPlainText("\n");

}

///////////////////////// QFile //////////////////////////////////
// QFile::copy
void Dialog::on_pushButton_8_clicked()
{
    showBtnInfo(sender());
    QString filename = ui->editFile->text();
    QString new_name = filename + ".bak";
    if (QFile::copy(filename, new_name))
        ui->plainTextEdit->appendPlainText("文件：" + filename + "复制为" + new_name);
    else
        ui->plainTextEdit->appendPlainText("文件：" + filename + "复制失败");
}


// QFile::exist
void Dialog::on_pushButton_9_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text();
    ui->plainTextEdit->appendPlainText((QFile::exists(sous) ? "文件存在" : "文件不存在"));
}

// QFile::remove
void Dialog::on_pushButton_10_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text();
    QFile file(sous);
    file.remove();
    ui->plainTextEdit->appendPlainText("删除文件：" + sous + "\n");
}

// QFile::rename
void Dialog::on_pushButton_11_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text();
    QFileInfo file_info(sous);
    QString newfile = file_info.path() + "/" + file_info.baseName() + ".xyz";
    QFile::rename(sous, newfile);
    ui->plainTextEdit->appendPlainText("源文件：" + sous);
    ui->plainTextEdit->appendPlainText("重命名为：" + newfile + "\n");
}

// QFile::moveToTrash
void Dialog::on_pushButton_12_clicked()
{
    showBtnInfo(sender());
    QString sous = ui->editFile->text();
    if (QFile::exists(sous)) {
        QFile::moveToTrash(sous);
        ui->plainTextEdit->appendPlainText("文件已被移动到回收站: " + sous + "\n");
    } else {
        ui->plainTextEdit->appendPlainText("文件不存在：" + sous + "\n");
    }
}

// QFile::copy 成员函数
void Dialog::on_pushButton_18_clicked()
{

}

// QFile::exist 成员函数
void Dialog::on_pushButton_19_clicked()
{

}

// QFile::remove 成员函数
void Dialog::on_pushButton_20_clicked()
{

}

// QFile::rename 成员函数
void Dialog::on_pushButton_21_clicked()
{

}

// QFile::moveToTrash 成员函数
void Dialog::on_pushButton_22_clicked()
{

}

///////////////////////// QFileInfo //////////////////////////////////


// QFileInfo::absoluteFilePath()
void Dialog::on_pushButton_13_clicked()
{

}

// QFileInfo::absolutePath()
void Dialog::on_pushButton_14_clicked()
{

}

// QFileInfo::fileName()
void Dialog::on_pushButton_15_clicked()
{

}

// QFileInfo::filePath()
void Dialog::on_pushButton_16_clicked()
{

}

// QFileInfo::size()
void Dialog::on_pushButton_17_clicked()
{

}

// QFileInfo::path()
void Dialog::on_pushButton_23_clicked()
{

}

// QFileInfo::baseName
void Dialog::on_pushButton_24_clicked()
{
    showBtnInfo(sender());
    QFileInfo file_info(ui->editFile->text());
    QString str = file_info.baseName();
    ui->plainTextEdit->appendPlainText("basename: " + str+"\n");
}

// QFileInfo::completeBaseName()
void Dialog::on_pushButton_25_clicked()
{

}

// QFileInfo::suffix()
void Dialog::on_pushButton_26_clicked()
{

}

// QFileInfo::completeSuffix()
void Dialog::on_pushButton_27_clicked()
{

}

// QFileInfo::isDir()
void Dialog::on_pushButton_28_clicked()
{

}

// QFileInfo::isFile()
void Dialog::on_pushButton_32_clicked()
{

}

// QFileInfo::isExecutable()
void Dialog::on_pushButton_29_clicked()
{

}

// QFileInfo::birthTime()
void Dialog::on_pushButton_33_clicked()
{

}

// QFileInfo::lastModified()
void Dialog::on_pushButton_30_clicked()
{

}

// QFileInfo::lastRead()
void Dialog::on_pushButton_34_clicked()
{

}

// QFileInfo::exist() 静态函数
void Dialog::on_pushButton_31_clicked()
{

}

// QFileInfo::exist()
void Dialog::on_pushButton_35_clicked()
{

}



///////////////////////// QDir //////////////////////////////////

// Qdir::tempPath()
void Dialog::on_pushButton_36_clicked()
{

}

// Qdir::rootPath()
void Dialog::on_pushButton_37_clicked()
{

}

// Qdir::homePath()
void Dialog::on_pushButton_38_clicked()
{

}

// QDir::drives
void Dialog::on_pushButton_39_clicked()
{
    showBtnInfo(sender());
    QFileInfoList drv_list = QDir::drives();
    for (int i = 0; i < drv_list.size(); i++)
        ui->plainTextEdit->appendPlainText(drv_list.at(i).path());
    ui->plainTextEdit->appendPlainText("\n");

}

// Qdir::currentPath()
void Dialog::on_pushButton_40_clicked()
{

}

// Qdir::setCurrent()
void Dialog::on_pushButton_41_clicked()
{

}

// Qdir::mkdir()
void Dialog::on_pushButton_42_clicked()
{

}

// Qdir::rmdir()
void Dialog::on_pushButton_43_clicked()
{

}

// Qdir::remove()
void Dialog::on_pushButton_44_clicked()
{

}

// Qdir::rename()
void Dialog::on_pushButton_45_clicked()
{

}

// Qdir::setPath()
void Dialog::on_pushButton_46_clicked()
{

}

// Qdir::removeRecursively()
void Dialog::on_pushButton_47_clicked()
{

}

// Qdir::absoluteFilePath()
void Dialog::on_pushButton_48_clicked()
{

}

// Qdir::absolutePath
void Dialog::on_pushButton_49_clicked()
{

}

// Qdir::canonicalPath()
void Dialog::on_pushButton_50_clicked()
{

}

// Qdir::filePath()
void Dialog::on_pushButton_51_clicked()
{

}

// Qdir::path()
void Dialog::on_pushButton_65_clicked()
{

}

// Qdir::dirName()
void Dialog::on_pushButton_66_clicked()
{

}

// Qdir::exists()
void Dialog::on_pushButton_67_clicked()
{

}

// Qdir::isEmpty()
void Dialog::on_pushButton_68_clicked()
{

}

// QDir::entryList(dir)
void Dialog::on_pushButton_69_clicked()
{
    showBtnInfo(sender());
    QDir dir(ui->editDir->text());
    QStringList strs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    ui->plainTextEdit->appendPlainText("所选目录下的所有目录：");
    for (int i = 0; i < strs.size(); i++)
        ui->plainTextEdit->appendPlainText(strs.at(i));
    ui->plainTextEdit->appendPlainText("\n");
}

// Qdir::entryList(file)
void Dialog::on_pushButton_70_clicked()
{

}




///////////////////////// QTemporaryDir //////////////////////////////////
// QTemporaryDir::系统目录创建临时文件夹
void Dialog::on_pushButton_52_clicked()
{
    showBtnInfo(sender());
    ui->plainTextEdit->appendPlainText("系统临时目录 = " + QDir::tempPath());
    QTemporaryDir dir;
    dir.setAutoRemove(true);
    ui->plainTextEdit->appendPlainText(dir.path() + "\n");
}

// QTemporaryDir::指定目录创建临时文件夹
void Dialog::on_pushButton_53_clicked()
{
    showBtnInfo(sender());
    QString spec_dir = ui->editDir->text();
    ui->plainTextEdit->appendPlainText("指定目录 = " + QDir::tempPath());
    QTemporaryDir dir(spec_dir + "/TempDir_xxxxxx");
    dir.setAutoRemove(false);
    ui->plainTextEdit->appendPlainText(dir.path() + "\n");
}

// QTemporaryDir::在当前目录创建临时文件夹
void Dialog::on_pushButton_54_clicked()
{
    showBtnInfo(sender());
    ui->plainTextEdit->appendPlainText("当前目录 = " + QDir::currentPath());
    QTemporaryDir dir("SubDir_xxxxxx");
    dir.setAutoRemove(false);
    ui->plainTextEdit->appendPlainText(dir.path() + "\n");
}


///////////////////////// QTemporaryFile //////////////////////////////////
// QTemporaryFile::系统目录创建临时文件
void Dialog::on_pushButton_55_clicked()
{
    showBtnInfo(sender());
    ui->plainTextEdit->appendPlainText("系统临时目录 = " + QDir::tempPath());
    QTemporaryFile file;
    file.setAutoRemove(true);
    file.open();
    ui->plainTextEdit->appendPlainText(file.fileName() + "\n");
    file.close();
}

// QTemporaryFile::指定目录创建临时文件
void Dialog::on_pushButton_56_clicked()
{
    showBtnInfo(sender());
    QString spec_dir = ui->editDir->text();
    ui->plainTextEdit->appendPlainText("指定目录 = " + spec_dir);
    QTemporaryFile file(spec_dir + "/MyFile_xxxxxx.tmp");
    file.setAutoRemove(false);
    file.open();
    ui->plainTextEdit->appendPlainText(file.fileName() + "\n");
    file.close();
}

// QTemporaryFile::当前目录创建临时文件
void Dialog::on_pushButton_57_clicked()
{
    showBtnInfo(sender());
    ui->plainTextEdit->appendPlainText("当前目录 = " + QDir::currentPath());
    QTemporaryFile file("/MyFile_xxxxxx.tmp");
    file.setAutoRemove(false);
    file.open();
    ui->plainTextEdit->appendPlainText(file.fileName() + "\n");
    file.close();
}



///////////////////////// QFileSystemWatcher //////////////////////////////////
// QFileSystemWatcher::addPath
void Dialog::on_pushButton_58_clicked()
{
    showBtnInfo(sender());
    ui->plainTextEdit->appendPlainText("监视目录：" + ui->editDir->text());
    file_watcher_.addPath(ui->editDir->text());
    file_watcher_.addPath(ui->editFile->text());
    connect(&file_watcher_, &QFileSystemWatcher::directoryChanged,
            this, &Dialog::do_directoryChanged);
    connect(&file_watcher_, &QFileSystemWatcher::fileChanged,
            this, &Dialog::do_fileChanged);
}

// QFileSystemWatcher::removePath
void Dialog::on_pushButton_59_clicked()
{
    showBtnInfo(sender());
    ui->plainTextEdit->appendPlainText("停止监视目录：" + ui->editDir->text());
    file_watcher_.removePath(ui->editDir->text());
    file_watcher_.removePath(ui->editFile->text());
    disconnect(&file_watcher_);
}

// QFileSystemWatcher::directories
void Dialog::on_pushButton_60_clicked()
{
    QStringList dirs = file_watcher_.directories();
    ui->plainTextEdit->appendPlainText("被监视的目录：");
    for (int i=0; i < dirs.size(); i++)
        ui->plainTextEdit->appendPlainText(dirs.at(i) + ", ");
    ui->plainTextEdit->appendPlainText("\n");
}

// QFileSystemWatcher::files
void Dialog::on_pushButton_61_clicked()
{
    QStringList files = file_watcher_.files();
    ui->plainTextEdit->appendPlainText("被监视的文件：");
    for (int i=0; i < files.size(); i++)
        ui->plainTextEdit->appendPlainText(files.at(i) + ", ");
    ui->plainTextEdit->appendPlainText("\n");
}






void Dialog::on_btnOpenFile_clicked()
{
    QString cur_dir = QDir::currentPath();
    QString file = QFileDialog::getOpenFileName(this, "打开一个文件", cur_dir, "所有文件(*.*)");
    ui->editFile->setText(file);
}


void Dialog::on_btnOpenDir_clicked()
{
    QString cur_dir = QDir::currentPath();
    QString dir = QFileDialog::getExistingDirectory(this, "选择一个目录", cur_dir, QFileDialog::ShowDirsOnly);
    ui->editDir->setText(dir);
}


void Dialog::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}


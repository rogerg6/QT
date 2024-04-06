#include "mainwindow.h"

#include <QApplication>
#include <dialoglogin.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DialogLogin *dlg_login = new DialogLogin;
    if (dlg_login->exec() == QDialog::Accepted) {
        MainWindow w;
        w.show();
        return a.exec();
    } else
        return 0;
}

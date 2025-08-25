#include "mainwindow.h"

#include <QApplication>
#include <QIcon>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QIcon icon(":/icon/myicon/HomeIcon.png"); // 使用资源路径或绝对路径
    w.setWindowIcon(icon);
    w.show();
    return a.exec();
}

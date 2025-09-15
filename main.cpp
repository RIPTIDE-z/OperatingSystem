#include "movingcar.h"

#include <QApplication>
// #include <QSystemTrayIcon>
// #include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 设置应用程序不在最后一个窗口关闭时退出以实现后台运行
    QApplication::setQuitOnLastWindowClosed(false);

    MovingCar w;
    w.show();
    return a.exec();
}

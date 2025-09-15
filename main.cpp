#include "movingcar.h"

#include <QApplication>
// #include <QSystemTrayIcon>
// #include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 检查系统是否支持系统托盘
    // if (!QSystemTrayIcon::isSystemTrayAvailable()) {
    //     QMessageBox::critical(nullptr, "系统托盘",
    //                           "系统不支持托盘功能，程序可能无法正常工作。");
    // }

    // 设置应用程序不在最后一个窗口关闭时退出
    QApplication::setQuitOnLastWindowClosed(false);

    MovingCar w;
    w.show();
    return a.exec();
}

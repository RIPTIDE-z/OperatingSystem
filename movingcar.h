#ifndef MOVINGCAR_H
#define MOVINGCAR_H

#include <QWidget>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QCloseEvent>
#include <QLabel>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
namespace Ui {
class MovingCar;
}
QT_END_NAMESPACE

class MovingCar : public QWidget
{
    Q_OBJECT

public:
    MovingCar(QWidget *parent = nullptr);
    ~MovingCar();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void moveCarStep();           // 定时器触发的小车移动
    void speedButtonClicked();// 速度按钮点击
    void showWindow();            // 从托盘恢复窗口
    void exitApplication();       // 退出应用程序

private:
    void initTrayIcon();         // 初始化系统托盘
    void updateSpeedDisplay();   // 更新速度显示

    Ui::MovingCar *ui;

    // 小车移动相关
    QTimer *moveTimer;
    int carX, carY;              // 小车当前位置
    int speedIndex;              // 当前速度索引
    int moveCount;               // 小车循环次数

    // 速度选项 {x增量, y增量}
    static const int SPEED_COUNT = 3;
    static const int speedOptions[SPEED_COUNT][2];
    static const char* speedNames[SPEED_COUNT];

    // 系统托盘
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QAction *restoreAction;
    QAction *exitAction;
};
#endif // MOVINGCAR_H

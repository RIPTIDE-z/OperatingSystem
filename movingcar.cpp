#include "movingcar.h"
#include "ui_movingcar.h"
#include <QApplication>
#include <QMessageBox>
#include <QPixmap>
#include <QStyle>

// 静态成员定义
const int MovingCar::speedOptions[SPEED_COUNT][2] = {
    {2, 2},   // 1x速度
    {4, 4},   // 2x速度
    {10, 10}    // 5x速度
};

const char* MovingCar::speedNames[SPEED_COUNT] = {
    "1x", "2x", "5x"
};

MovingCar::MovingCar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MovingCar)
    , moveTimer(new QTimer(this))
    , carX(0)
    , carY(0)
    , speedIndex(0)
    , moveCount(0)
    , trayIcon(nullptr)
{
    ui->setupUi(this);

    // 设置窗口属性
    setWindowTitle("移动小车实验");
    setFixedSize(600, 600);

    // 设置小车图片
    QPixmap carPixmap(":/images/car.png");
    if (carPixmap.isNull()) {
        // 如果没有图片资源，创建简单的文本标识
        ui->carLabel->setText("🚗");
        ui->carLabel->setStyleSheet("font-size: 24px;");
    } else {
        // 缩放图片到合适大小
        carPixmap = carPixmap.scaled(40, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        // 将carlabel设置为图片
        ui->carLabel->setPixmap(carPixmap);
    }

    // 初始化小车位置
    ui->carLabel->move(carX, carY);

    // 初始化速度显示
    updateSpeedDisplay();

    // 连接信号和槽
    connect(ui->speedButton, &QPushButton::clicked, this, &MovingCar::on_speedButton_clicked);
    connect(moveTimer, &QTimer::timeout, this, &MovingCar::moveCarStep);

    // 初始化系统托盘
    initTrayIcon();

    // 启动定时器（50ms间隔，模拟时钟中断）
    moveTimer->start(50);
}

MovingCar::~MovingCar()
{
    delete ui;
}

void MovingCar::initTrayIcon()
{
    // 创建托盘菜单
    trayMenu = new QMenu(this);
    restoreAction = new QAction("恢复", this);
    exitAction = new QAction("退出", this);

    trayMenu->addAction(restoreAction);
    trayMenu->addSeparator();
    trayMenu->addAction(exitAction);

    // 连接托盘菜单信号
    connect(restoreAction, &QAction::triggered, this, &MovingCar::showWindow);
    connect(exitAction, &QAction::triggered, this, &MovingCar::exitApplication);

    // 创建系统托盘图标
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayMenu);
    trayIcon->setToolTip("移动小车程序");

    // 设置托盘图标
    QIcon icon(":/images/car.png");
    if (icon.isNull()) {
        icon = style()->standardIcon(QStyle::SP_ComputerIcon);
    }
    trayIcon->setIcon(icon);
}

void MovingCar::moveCarStep()
{
    // 计算新位置
    int newX = carX + speedOptions[speedIndex][0];
    int newY = carY + speedOptions[speedIndex][1];

    // 检查边界，超出则重置到左上角
    if (newX >= width() - ui->carLabel->width() ||
        newY >= height() - ui->carLabel->height() - 60) { // 为底部控件留空间
        newX = 0;
        newY = 0;

        moveCount += 1;
        ui->movecountLabel->setText(QString("%1").arg(moveCount));
        // 更新循环次数
    }

    carX = newX;
    carY = newY;

    // 更新小车位置
    ui->carLabel->move(carX, carY);
}

void MovingCar::on_speedButton_clicked()
{
    // 切换到下一个速度
    speedIndex = (speedIndex + 1) % SPEED_COUNT;
    updateSpeedDisplay();
}

void MovingCar::updateSpeedDisplay()
{
    ui->speedButton->setText(QString("%1 速度").arg(speedNames[speedIndex]));
    ui->statusLabel->setText(QString("当前速度: %1").arg(speedNames[speedIndex]));
}

void MovingCar::showWindow()
{
    show();
    raise();
    activateWindow();
    if(trayIcon){
        trayIcon->hide();
    }
}

void MovingCar::exitApplication()
{
    moveTimer->stop();
    if (trayIcon) {
        trayIcon->hide();
    }
    QApplication::quit();
}

void MovingCar::closeEvent(QCloseEvent *event)
{
    if (trayIcon && !trayIcon->isVisible()) {
        QMessageBox::information(this, "系统托盘",
                                 "程序将在后台继续运行。\n"
                                 "右键托盘图标可以恢复或退出程序。");
        hide();
        trayIcon->show(); // 显示托盘图标
        event->ignore();  // 忽略关闭事件，程序继续运行
    }
}

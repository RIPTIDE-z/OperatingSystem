#include "movingcar.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MovingCar w;
    w.show();

    return a.exec();
}

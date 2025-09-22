#include "plant_monitor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    plant_monitor w;
    w.show();
    return a.exec();
}

#include "di/di.h"

#include <QCoreApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DI di;
    di.setup();

    return a.exec();
}

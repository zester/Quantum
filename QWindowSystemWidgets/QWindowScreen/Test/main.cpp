#include <QDebug>
#include <QtCore/QCoreApplication>

#include "../qwindowscreen.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QWindowScreen screen;

    qDebug() << screen.width();
    qDebug() << screen.height();
    qDebug() << screen.refreshRate();
    qDebug() << screen.rotation();
    qDebug() << screen.screens();

    return a.exec();
}

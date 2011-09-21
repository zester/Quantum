#ifndef QWINDOWSYSTEM_H
#define QWINDOWSYSTEM_H

#include <QWidget>

typedef QList<WId> WindowList;

class QWindowSystem
{
public:
    static WindowList windows();
    static WId activeWindow();
    static WId findWindow(const QString& title);
    static WId windowAt(const QPoint& pos);
    static QString windowTitle(WId window);
    static QStringList windowTitles();
    static QRect windowGeometry(WId window);

    static uint idleTime();
};

#endif // QWINDOWSYSTEM_H

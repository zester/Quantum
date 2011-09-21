#include "qxtwindowsystem.h"

#include <QStringList>

QStringList QWindowSystem::windowTitles()
{
    WindowList windows = QWindowSystem::windows();
    QStringList titles;
    foreach(WId window, windows)
    titles += QWindowSystem::windowTitle(window);
    return titles;
}

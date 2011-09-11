#ifndef QDESKTOPMENU_H
#define QDESKTOPMENU_H

#include <QMenu>
#include <QDebug>

class QDesktopMenu : public QMenu
{
    Q_OBJECT
public:
    explicit QDesktopMenu(QWidget *parent = 0);

signals:

public slots:
    void createFolder();
    void createLauncher();
    void createEmptyFile();
};

#endif // QDESKTOPMENU_H

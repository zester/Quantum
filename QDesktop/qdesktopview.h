#ifndef QDESKTOPVIEWWIDGET_H
#define QDESKTOPVIEWWIDGET_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QMenu>
//#include <QSettings>
#include "qdesktopviewitem.h"
#include <QFileSystemWatcher>
#include "qdesktopmenu.h"
#include "qiconmenu.h"

class QDesktopViewWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit QDesktopViewWidget(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *);


public slots:
    void iconClicked(QListWidgetItem*);
    void populatedDesktop();

private:
    QPoint startPos;
    QDesktopMenu *menu;
    QIconMenu *iconMenu;
    QFileSystemWatcher *desktopDir;

signals:


};

#endif // QDESKTOPVIEWWIDGET_H

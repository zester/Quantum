/*
Copyright (C) 2011 by Steven Starr

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef QDESKTOPVIEWWIDGET_H
#define QDESKTOPVIEWWIDGET_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QMenu>
#include <QSettings>
#include "qdesktopviewitem.h"
#include <QFileSystemWatcher>
#include "qiconmenu.h"

class QDesktopViewWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit QDesktopViewWidget(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *);


public slots:
    void iconClicked(QListWidgetItem*);
    void layoutDirection();
    void populatedDesktop();
    void resizeIcons();
    void createFolder();
    void createLauncher();
    void createEmptyFile();
    void showDesktopIcons();
    void execDesktopSettings();

private:
    QPoint startPos;
    QIconMenu *iconMenu;
    QMenu *menu;
    QFileSystemWatcher *desktopDir;
    QFileSystemWatcher *mtabFile;
    QAction *showIcons;
    QSettings *dSettings;
    QAction *leftToRight;
    QAction *rightToLeft;
    QAction *extraLargeIcons;
    QAction *largeIcons;
    QAction *mediumIcons;
    QAction *smallIcons;

signals:


};

#endif // QDESKTOPVIEWWIDGET_H

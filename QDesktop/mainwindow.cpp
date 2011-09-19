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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //
    setAttribute(Qt::WA_X11NetWmWindowTypeDesktop);
    resize(QApplication::desktop()->size());

    // See reloadWallpaper() function for description
    reloadWallpaper();

    //
    desktopView = new QDesktopViewWidget;
    setCentralWidget(desktopView);


    // Watch .config/chipara/desktop.conf for changes
    configFile = new QFileSystemWatcher;
    QString confPath = QString(getenv("QDESKTOP_CONFIG"));
    configFile->addPath(confPath);

    // When .config/chipara/desktop.conf changes trigger reloadWallpaper() function
    connect(configFile, SIGNAL(fileChanged(QString)), this, SLOT(reloadWallpaper()));

}

//  Application resize event
void MainWindow::resizeEvent(QResizeEvent *event) // Note: Function argument needs to be made void?
{
    // Scale wallpaper to desktop
    wallpaper = wallpaper.scaled(QApplication::desktop()->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

// Application paint event
void MainWindow::paintEvent(QPaintEvent *event) // Note: Function argument needs to be made void?
{
    // Paint wallpaper on MainWindow
    QPainter p(this);
    p.drawPixmap(QPoint(0,0), wallpaper);
}

//
void MainWindow::reloadWallpaper() // Rename to loadWallpaper()?
{
    // Load .config/chipara/desktop.conf read and set wallpaper, icon theme
    windowSettings = new QSettings("chipara", "desktop");
    windowSettings->beginGroup("window");
    wallpaper.load(windowSettings->value("wallpaper").toString());
    QIcon::setThemeName(windowSettings->value("iconTheme").toString());
    windowSettings->endGroup();

    // Scale wallpaper to desktop
    wallpaper = wallpaper.scaled(QApplication::desktop()->size());

    // Repaint wallpaper to MainWindow
    this->repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}

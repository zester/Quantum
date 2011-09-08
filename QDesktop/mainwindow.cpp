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

    reloadWallpaper();

    //
    desktopView = new QDesktopViewWidget;
    setCentralWidget(desktopView);

    configFile = new QFileSystemWatcher;
    configFile->addPath("/home/steven/.config/chipara/desktop.conf");

    connect(configFile, SIGNAL(fileChanged(QString)), this, SLOT(reloadWallpaper()));

}

//
void MainWindow::resizeEvent(QResizeEvent *event) // Note: Function argument needs to be made void?
{
    //
    wallpaper = wallpaper.scaled(QApplication::desktop()->size());
}

//
void MainWindow::paintEvent(QPaintEvent *event) // Note: Function argument needs to be made void?
{
    //
    QPainter p(this);
    p.drawPixmap(QPoint(0,0), wallpaper);
}

void MainWindow::reloadWallpaper()
{
    // Note: Needs to be moved to a class function of it's own
    //
    windowSettings = new QSettings("chipara", "desktop");
    windowSettings->beginGroup("window");
    wallpaper.load(windowSettings->value("wallpaper").toString());
    windowSettings->endGroup();

    wallpaper = wallpaper.scaled(QApplication::desktop()->size());

    this->repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}

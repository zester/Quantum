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

    //
    desktopView = new QDesktopViewWidget;
    setCentralWidget(desktopView);

    //
    wallpaper.load("/home/steven/Picture/Arch_Linux_Wallpaper_by_james66.jpg");

}

//
void MainWindow::resizeEvent(QResizeEvent *event) // Note: Function argument needs to be made void
{
    //
    wallpaper = wallpaper.scaled(QApplication::desktop()->size());
}

//
void MainWindow::paintEvent(QPaintEvent *event) // Note: Function argument needs to be made void
{
    //
    QPainter p(this);
    p.drawPixmap(QPoint(0,0), wallpaper);
}


MainWindow::~MainWindow()
{
    delete ui;
}

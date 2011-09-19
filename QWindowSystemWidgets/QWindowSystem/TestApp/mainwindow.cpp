#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList titles = QxtWindowSystem::windowTitles();

    for (int i = 0; i < titles.size(); ++i)
           qDebug() << titles.at(i) << endl;

    /*
    WindowList windows = QxtWindowSystem::windows();
    QStringList titles;
    foreach(WId window, windows)
        titles += QxtWindowSystem::windowTitle(window);
        qDebug() << titles << endl;
     */
}

MainWindow::~MainWindow()
{
    delete ui;
}

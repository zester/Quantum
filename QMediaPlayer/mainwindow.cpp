#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QDesktopServices>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QIcon::setThemeName("oxygen");

    instance = new VlcInstance(VlcCommon::args(), this);
    player = new VlcMediaPlayer(ui->video->widgetId(), this);
    ui->video->setRatio1_1();
    ui->volume->setVolume(50);
    //player->open("/home/steven/The.Dead.2010.BRRip.RERIP.XviD.OCW_ns.avi");

    QPixmap logo;
    logo.load(":/images/logo.svg");
    //logo = logo.scaled(QSize(128, 128));
    ui->label->setPixmap(logo);

    ui->actionPlay->setIcon(QIcon::fromTheme("media-playback-start"));
    ui->actionPause->setIcon(QIcon::fromTheme("media-playback-pause"));
    connect(ui->actionPause, SIGNAL(triggered()), player, SLOT(pause()));

    ui->actionStop->setIcon(QIcon::fromTheme("media-playback-stop"));
    ui->actionOpen->setIcon(QIcon::fromTheme("document-open-folder"));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));

}

void MainWindow::open()
{
    QString movieLocation = QDesktopServices::storageLocation(QDesktopServices::MoviesLocation);
    qDebug() << movieLocation << endl;

    QString file = QFileDialog::getOpenFileName(this, "Open file or URL", movieLocation, "Multimedia files(*)");

    if (file.isEmpty())
        return;

    player->open(file);
    ui->stackedWidget->setCurrentIndex(1);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete instance;
    delete player;
}

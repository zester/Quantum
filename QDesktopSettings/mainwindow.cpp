#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfoList>
#include <QFileInfo>
#include <QDesktopServices>
#include <QString>
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QIcon::setThemeName("oxygen");

    setWindowTitle("Desktop Settings");
    setWindowIcon(QIcon::fromTheme("preferences-desktop"));

    QIcon fakeIcon = QIcon::fromTheme("preferences-desktop");
    QPixmap pixmap = fakeIcon.pixmap(QSize(24, 24), QIcon::Normal, QIcon::On);

    ui->label_3->setPixmap(pixmap);

    QString pictures = QDesktopServices::storageLocation(QDesktopServices::PicturesLocation);

    QDir dir(pictures);
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);

    QFileInfoList list = dir.entryInfoList();
    qDebug() << list.size() << endl;


    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        QPixmap thumbNail;
        thumbNail.load(pictures + "/" +fileInfo.fileName());
        thumbNail = thumbNail.scaled(QSize(24, 24));
        ui->comboBox->addItem(QIcon(thumbNail), fileInfo.fileName());
    }

    dSettings = new QSettings("chipara", "desktop");
    dSettings->beginGroup("window");
    ui->wallpaperPreview->setPixmap(QPixmap(dSettings->value("wallpaper").toString()));
    dSettings->endGroup();

    connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(setWallpaper(QString)));
    connect(ui->applyButton, SIGNAL(clicked()), this, SLOT(applySettings()));

}

void MainWindow::setWallpaper(QString index)
{
    QString picturesLoc = QDesktopServices::storageLocation(QDesktopServices::PicturesLocation) + "/" +index;
    qDebug() << picturesLoc << endl;
    ui->wallpaperPreview->setPixmap(QPixmap(picturesLoc));
}

void MainWindow::applySettings()
{
    QString picturesLoc = QDesktopServices::storageLocation(QDesktopServices::PicturesLocation) + "/" + ui->comboBox->currentText();
    dSettings = new QSettings("chipara", "desktop");
    dSettings->beginGroup("window");
    dSettings->setValue("wallpaper", picturesLoc);
    dSettings->endGroup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

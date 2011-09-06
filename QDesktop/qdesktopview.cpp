#include "qdesktopview.h"
#include <QDebug>
#include <QIcon>
#include <QString>
#include <QMenu>
#include <QFileInfoList>
#include <QFileInfo>
#include <QSettings>
#include <QDir>
#include <QDesktopServices>
#include <QDesktopWidget>
#include "freedesktopmime.h"

QDesktopViewWidget::QDesktopViewWidget(QWidget *parent) :
    QListWidget(parent)
{
    //
    setStyleSheet("QListView {background-color: transparent; color: white;}");

    //
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setViewMode(QListView::IconMode);
    setSpacing(20);
    setFlow(QListView::TopToBottom);
    setMovement(QListView::Snap);
    setLayoutMode(QListView::Batched);
    setBatchSize(100);
    setMovement(QListView::Snap);
    setIconSize(QSize(48, 48));
    setWordWrap(true);
    setWrapping(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSortingEnabled(true);
    setLayoutDirection(Qt::LeftToRight);
    setSelectionRectVisible(true);
    setTextElideMode(Qt::ElideMiddle);
    setDragEnabled(true);
    setFrameStyle(0);
    setFrameShape(QFrame::NoFrame);
    setAutoScroll(true);
    setResizeMode(QListView::Adjust);

    //setDragEnabled(true);
    //this->viewport()->setAcceptDrops(true);
    //setDropIndicatorShown(true);
    //setDragDropMode(QAbstractItemView::InternalMove);

    //
    QFreeDesktopMime mime;

    //
    QString desktop = QDesktopServices::storageLocation( QDesktopServices::DesktopLocation );

    //
    QDir dir(desktop);
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);

    //
    QFileInfoList list = dir.entryInfoList();

    //
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        QString file = fileInfo.fileName();

        // Parse avalable .desktop files
        if (file.endsWith(".desktop", Qt::CaseInsensitive) == true) {
            QSettings settings(dir.absoluteFilePath(fileInfo.fileName()), QSettings::IniFormat);
            settings.beginGroup("Desktop Entry");
            this->addItem(new QListWidgetItem(QIcon::fromTheme(settings.value("Icon").toString()), \
                                                               settings.value("Name").toString()));
            settings.endGroup();

        // For files on the desktop that are not a .desktop file
        }else{
            this->addItem(new QListWidgetItem(QIcon::fromTheme(mime.genericIconName(mime.fromFile(fileInfo.absoluteFilePath()))), \
                                              fileInfo.fileName()));
        }
    }

    // Right Click Desktop Menu
    menu = new QMenu(this);
    menu->setStyleSheet("padding-left: 10px; padding-right: 10px; padding-top: 5px; padding-bottom: 5px;");

    // Create New Folder
    QAction *createFolder = new QAction(QIcon::fromTheme("folder"), tr("&Create Folder"), this);
    createFolder->setCheckable(false);
    menu->addAction(createFolder);
    connect(createFolder, SIGNAL(triggered()), this, SLOT(createFolder()));

    // Create Launcher
    QAction *createLauncher = new QAction(QIcon::fromTheme("folder"), tr("&Create Launcher ..."), this);
    createLauncher->setCheckable(false);
    menu->addAction(createLauncher);
    connect(createLauncher, SIGNAL(triggered()), this, SLOT(createLauncher()));

    //
    QMenu *createDocMenu = menu->addMenu(tr("&Create Document"));

    // Create Launcher
    QAction *createEmptyFile = new QAction(QIcon::fromTheme("folder"), tr("&Empty File"), this);
    createEmptyFile->setCheckable(false);
    createDocMenu->addAction(createEmptyFile);
    connect(createEmptyFile, SIGNAL(triggered()), this, SLOT(createEmptyFile()));

    //
    menu->addSeparator();



    // Right Click Desktop Icon Menu
    iconMenu = new QMenu(this);
    iconMenu->setStyleSheet("padding: 5px; width: 220px;");
    iconMenu->addAction(new QAction(QIcon::fromTheme("folder"), "Create Folder", this));

    // Desktop Icon Double Click Event
    connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(iconClicked(QListWidgetItem*)));

}

//
void QDesktopViewWidget::createFolder()
{

    qDebug() << "Create Folder Action Triggered";
}

//
void QDesktopViewWidget::createLauncher()
{

    qDebug() << "Create Launcher Action Triggered";
}

//
void QDesktopViewWidget::createEmptyFile()
{

    qDebug() << "Create Empty File Action Triggered";
}

//
void QDesktopViewWidget::mousePressEvent(QMouseEvent *event)
{
    //
    startPos = event->globalPos();

    //
    QListWidgetItem *item = 0;
    item = this->itemAt(startPos);

    //
    if (event->button() == Qt::RightButton)
        if (item == 0)
        {
            menu->exec(startPos);
            //qDebug() << "Desktop Right Clicked" << "\n";
        } else {
            iconMenu->exec(startPos);
            //qDebug() << "Icon Right Clicked" << "\n";
        }

    QListWidget::mousePressEvent(event); // Note: sure if this is needed
}

//
void QDesktopViewWidget::iconClicked(QListWidgetItem* icon)
{
    qDebug() << icon->text() << "\n";
}

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


// Note: the QDesktopViewWidget Class will become it's own widget
// so others can easly create there own desktopsor file managers with
// only a few lines of code
QDesktopViewWidget::QDesktopViewWidget(QWidget *parent) :
    QListWidget(parent)
{
    // This sets the QDesktopViewWidget(QListWidget) to transparent so that the
    // desktop wallpaper below it can be seen. Note: the color: white propertiy
    // needs to be moved to the desktop config file
    setStyleSheet("QListView {background-color: transparent; color: white;}");

    // Note: Need to check if config files exist, if it doesnt we need to
    // create it.

    // In the future the below QDesktopViewWidget settings will be wrapped
    // in this block of code so every aspect of how the desktop looks and feels
    // can be configured.

    // Note: Needs to be moved to a class function of it's own
    //desktopSettings = new QSettings("chipara", "desktop");
    //desktopSettings->beginGroup("desktop");
    //desktopSettings->endGroup();

    // Variouse settings for the QDesktopViewWidget(QListWidget) class
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

    // The FreeDesktopMime class tells use what the mimetype of a file is and its mimetype icon
    QFreeDesktopMime mime;

    // Location of the desktop
    QString desktop = QDesktopServices::storageLocation( QDesktopServices::DesktopLocation );

    // Set current dir to the desktop location specified above
    QDir dir(desktop);
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); // Show all files/directorys excepts . and ..

    //
    QFileInfoList list = dir.entryInfoList();

    // Iterate over all the files found in the current dir
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

    // Create submenu for Create Document
    QMenu *createDocMenu = menu->addMenu(tr("&Create Document"));

    // Create Launcher
    QAction *createEmptyFile = new QAction(QIcon::fromTheme("folder"), tr("&Empty File"), this);
    createEmptyFile->setCheckable(false);
    createDocMenu->addAction(createEmptyFile);
    connect(createEmptyFile, SIGNAL(triggered()), this, SLOT(createEmptyFile()));

    // Add a separator to the menu
    menu->addSeparator();


    // Right Click Desktop Icon Menu
    iconMenu = new QMenu(this);
    iconMenu->setStyleSheet("padding: 5px; width: 220px;");
    iconMenu->addAction(new QAction(QIcon::fromTheme("folder"), "Create Folder", this));

    // Desktop Icon Double Click Event
    connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(iconClicked(QListWidgetItem*)));

}

// Right Click Desktop Menu Create Folder Action
void QDesktopViewWidget::createFolder()
{
    qDebug() << "Create Folder Action Triggered";
}

// Right Click Desktop Menu Create Launcher(.desktop) Action
void QDesktopViewWidget::createLauncher()
{
    qDebug() << "Create Launcher Action Triggered";
}

// Right Click Desktop Menu Create Empty File(.txt) Action
void QDesktopViewWidget::createEmptyFile()
{
    qDebug() << "Create Empty File Action Triggered";
}

// Right Click Mouse Events on the Desktop & Desktop Icon
void QDesktopViewWidget::mousePressEvent(QMouseEvent *event)
{
    // Position of the Mouse Cursor when it receved the click event
    startPos = event->globalPos();

    //
    QListWidgetItem *item = 0;
    item = this->itemAt(startPos);

    //
    if (event->button() == Qt::RightButton)
    {
        if (item == 0)
        {
            menu->exec(startPos);
            //qDebug() << "Desktop Right Clicked" << "\n";
        } else {
            iconMenu->exec(startPos);
            //qDebug() << "Icon Right Clicked" << "\n";
        }
    }

    QListWidget::mousePressEvent(event); // Note: sure if this is needed
}

// Left Click Mouse Events on the Desktop Icon
void QDesktopViewWidget::iconClicked(QListWidgetItem* icon)
{
    qDebug() << icon->text() << "\n";
}

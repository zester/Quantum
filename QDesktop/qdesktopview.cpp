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
#include <QProcess>
#include <QActionGroup>


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
    setUniformItemSizes(true);
    //setWordWrap(true);
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

    //
    populatedDesktop();

    // Right Click Desktop Menu
    menu = new QMenu(this);

    // Create submenu for Create Document
    QMenu *viewMenu = menu->addMenu(tr("&View"));
    QActionGroup *viewGroup = new QActionGroup(this);

    // Large Icons
    QAction *extraLargeIcons = new QAction(QIcon::fromTheme("folder"), "X-Large Icons", this);
    extraLargeIcons->setCheckable(true);
    viewGroup->addAction(extraLargeIcons);
    viewMenu->addAction(extraLargeIcons);
    connect(extraLargeIcons, SIGNAL(triggered()), this, SLOT(setIconsExtraLarge()));

    // Large Icons
    QAction *largeIcons = new QAction(QIcon::fromTheme("folder"), "Large Icons", this);
    largeIcons->setCheckable(true);
    viewGroup->addAction(largeIcons);
    viewMenu->addAction(largeIcons);
    connect(largeIcons, SIGNAL(triggered()), this, SLOT(setIconsLarge()));

    // Medium Icons
    QAction *mediumIcons = new QAction(QIcon::fromTheme("folder"), "Medium Icons", this);
    mediumIcons->setCheckable(true);
    mediumIcons->setChecked(true);
    viewGroup->addAction(mediumIcons);
    viewMenu->addAction(mediumIcons);
    connect(mediumIcons, SIGNAL(triggered()), this, SLOT(setIconsMedium()));

    // Medium Icons
    QAction *smallIcons = new QAction(QIcon::fromTheme("folder"), "Small Icons", this);
    smallIcons->setCheckable(true);
    viewGroup->addAction(smallIcons);
    viewMenu->addAction(smallIcons);
    connect(smallIcons, SIGNAL(triggered()), this, SLOT(setIconsSmall()));

    // Add a separator to the menu
    viewMenu->addSeparator();

    // Sort By Size
    QAction *showIcons = new QAction(QIcon::fromTheme("folder"), "Show Desktop Icons", this);
    showIcons->setCheckable(true);
    showIcons->setChecked(true);
    viewMenu->addAction(showIcons);

    // Create submenu for Create Document
    QMenu *sortMenu = menu->addMenu(tr("&Sort By"));
    QActionGroup *sortGroup = new QActionGroup(this);

    // Sort By Name
    QAction *nameSort = new QAction(QIcon::fromTheme("folder"), "Name", this);
    nameSort->setCheckable(true);
    nameSort->setChecked(true);
    sortGroup->addAction(nameSort);
    sortMenu->addAction(nameSort);

    // Sort By Size
    QAction *sizeSort = new QAction(QIcon::fromTheme("folder"), "Size", this);
    sizeSort->setCheckable(true);
    sortGroup->addAction(sizeSort);
    sortMenu->addAction(sizeSort);

    // Sort By Size
    QAction *typeSort = new QAction(QIcon::fromTheme("folder"), "Item Type", this);
    typeSort->setCheckable(true);
    sortGroup->addAction(typeSort);
    sortMenu->addAction(typeSort);

    // Sort By Size
    QAction *dateSort = new QAction(QIcon::fromTheme("folder"), "Date Modified", this);
    dateSort->setCheckable(true);
    sortGroup->addAction(dateSort);
    sortMenu->addAction(dateSort);

    // Refresh
    QAction *refresh = new QAction(QIcon::fromTheme("folder"), "Refresh", this);
    menu->addAction(refresh);

    // Add a separator to the menu
    menu->addSeparator();

    // Paste
    QAction *paste = new QAction(QIcon::fromTheme("folder"), "Paste", this);
    paste->setEnabled(false);
    menu->addAction(paste);

    // Paste Shortcut
    QAction *pasteShortCut = new QAction(QIcon::fromTheme("folder"), "Paste Shortcut", this);
    pasteShortCut->setEnabled(false);
    menu->addAction(pasteShortCut);

    // Add a separator to the menu
    menu->addSeparator();

    // New Menu
    QMenu *create = menu->addMenu(tr("&New"));

    // Create Folder
    QAction *createFolder = new QAction(QIcon::fromTheme("folder"), tr("&Folder"), this);
    create->addAction(createFolder);
    createFolder->setIconVisibleInMenu(true);
    connect(createFolder, SIGNAL(triggered()), this, SLOT(createFolder()));

    // Create Launcher
    QAction *createLauncher = new QAction(QIcon::fromTheme("application-x-desktop"), tr("&Launcher"), this);
    create->addAction(createLauncher);
    createLauncher->setIconVisibleInMenu(true);
    connect(createLauncher, SIGNAL(triggered()), this, SLOT(createLauncher()));

    // Create Empty File
    QAction *createEmptyFile = new QAction(QIcon::fromTheme("text-plain"), tr("&Empty File"), this);
    create->addAction(createEmptyFile);
    createEmptyFile->setIconVisibleInMenu(true);
    connect(createEmptyFile, SIGNAL(triggered()), this, SLOT(createEmptyFile()));

    // Add a separator to the menu
    menu->addSeparator();

    // Paste
    QAction *desktopSettings = new QAction(QIcon::fromTheme("preferences-desktop"), "Desktop Settings", this);
    desktopSettings->setIconVisibleInMenu(true);
    menu->addAction(desktopSettings);



    // Right Click Desktop Icon Menu
    iconMenu = new QIconMenu(this);


    //
    desktopDir = new QFileSystemWatcher;
    desktopDir->addPath(QDesktopServices::storageLocation(QDesktopServices::DesktopLocation));

    // Desktop Icon Double Click Event
    connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(iconClicked(QListWidgetItem*)));
    connect(desktopDir, SIGNAL(directoryChanged(QString)), this, SLOT(populatedDesktop()));
}


void QDesktopViewWidget::populatedDesktop()
{
    this->clear();

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
            QDesktopViewItem *icon;
            this->addItem(icon = new QDesktopViewItem(QIcon::fromTheme(settings.value("Icon").toString()), \
                                               settings.value("Name").toString()));
            icon->setData(Qt::UserRole, QVariant(fileInfo.absoluteFilePath()));

            settings.endGroup();

        // For files on the desktop that are not a .desktop file
        }else{
            this->addItem(new QDesktopViewItem(QIcon::fromTheme(mime.genericIconName(mime.fromFile(fileInfo.absoluteFilePath()))), \
                                              fileInfo.fileName()));
        }
    }

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
    qDebug() << icon->data(Qt::UserRole).toString() << "\n";
    QProcess commandLine;


    qDebug() << icon->data(Qt::UserRole).toString() << "\n";

    QSettings settings(icon->data(Qt::UserRole).toString(), QSettings::IniFormat);
    settings.beginGroup("Desktop Entry");
        qDebug() << settings.value("Name").toString();
        commandLine.startDetached(settings.value("Exec").toString());
        qDebug() << settings.value("Exec").toString();
        qDebug() << settings.value("Icon").toString();
        qDebug() << settings.value("Type").toString();
        // Defect cant git list

        qDebug() << settings.value("Categories").toString();
        qDebug() << settings.value("GenericName").toString();
        qDebug() << settings.value("Terminal").toString();
        qDebug() << settings.value("MimeType").toString();
    settings.endGroup();

}

// Set Desktop Icons to Large
void QDesktopViewWidget::setIconsExtraLarge()
{
    qDebug() << "setIconsLarge";
    this->setIconSize(QSize(128, 128));
    this->populatedDesktop();
}

// Set Desktop Icons to Large
void QDesktopViewWidget::setIconsLarge()
{
    qDebug() << "setIconsLarge";
    this->setIconSize(QSize(64, 64));
    this->populatedDesktop();
}

// Set Desktop Icons to Large
void QDesktopViewWidget::setIconsMedium()
{
    qDebug() << "setIconsMedium";
    this->setIconSize(QSize(48, 48));
    this->populatedDesktop();
}

// Set Desktop Icons to Large
void QDesktopViewWidget::setIconsSmall()
{
    qDebug() << "setIconsSmall";
    this->setIconSize(QSize(36, 36));
    this->populatedDesktop();
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

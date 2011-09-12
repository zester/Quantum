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

    //
    populatedDesktop();

    // Right Click Desktop Menu
    menu = new QDesktopMenu(this);

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

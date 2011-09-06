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
    menu->setStyleSheet("padding: 5px; width: 220px;");
    menu->addAction(new QAction(QIcon::fromTheme("folder"), "Create Folder", this));
    menu->addAction(new QAction(QIcon::fromTheme("folder"), "Create Launcher ...", this));
    menu->addAction(new QAction(QIcon::fromTheme("file"),   "Create Document", this));
    menu->addSeparator();
    menu->addAction(new QAction(QIcon::fromTheme("file"),   "Organize Desktop by Name", this));
    menu->addAction(new QAction(QIcon::fromTheme("file"),   "Keep Aligned", this));
    menu->addSeparator();
    menu->addAction(new QAction(QIcon::fromTheme("file"),   "Paste", this));
    menu->addAction(new QAction(QIcon::fromTheme("file"),   "Select All", this));
    menu->addSeparator();
    menu->addAction(new QAction(QIcon::fromTheme("file"),   "Change Desktop Background", this));


    // Right Click Desktop Icon Menu
    iconMenu = new QMenu(this);
    iconMenu->setStyleSheet("padding: 5px; width: 220px;");
    iconMenu->addAction(new QAction(QIcon::fromTheme("folder"), "Create Folder", this));

    // Desktop Icon Double Click Event
    connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(iconClicked(QListWidgetItem*)));

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

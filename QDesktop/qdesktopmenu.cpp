#include "qdesktopmenu.h"

QDesktopMenu::QDesktopMenu(QWidget *parent) :
    QMenu(parent)
{
    // Create New Folder
    QAction *createFolder = new QAction(QIcon::fromTheme("folder"), tr("&Create Folder"), this);
    this->addAction(createFolder);
    connect(createFolder, SIGNAL(triggered()), this, SLOT(createFolder()));

    // Create Launcher
    QAction *createLauncher = new QAction(QIcon::fromTheme("folder"), tr("&Create Launcher ..."), this);
    this->addAction(createLauncher);
    connect(createLauncher, SIGNAL(triggered()), this, SLOT(createLauncher()));

    // Create submenu for Create Document
    QMenu *createDocMenu = this->addMenu(tr("&Create Document"));

    // Create Launcher
    QAction *createEmptyFile = new QAction(QIcon::fromTheme("folder"), tr("&Empty File"), this);
    createDocMenu->addAction(createEmptyFile);
    connect(createEmptyFile, SIGNAL(triggered()), this, SLOT(createEmptyFile()));

    // Add a separator to the menu
    this->addSeparator();
}

// Right Click Desktop Menu Create Folder Action
void QDesktopMenu::createFolder()
{
    qDebug() << "Create Folder Action Triggered";
}

// Right Click Desktop Menu Create Launcher(.desktop) Action
void QDesktopMenu::createLauncher()
{
    qDebug() << "Create Launcher Action Triggered";
}

// Right Click Desktop Menu Create Empty File(.txt) Action
void QDesktopMenu::createEmptyFile()
{
    qDebug() << "Create Empty File Action Triggered";
}

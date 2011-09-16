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

#include <QAction>
#include "qdesktopmenu.h"

QDesktopMenu::QDesktopMenu(QWidget *parent) :
    QMenu(parent)
{

    // Create submenu for Create Document
    QMenu *viewMenu = this->addMenu(tr("&View"));
    QActionGroup *viewGroup = new QActionGroup(this);

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
    QMenu *sortMenu = this->addMenu(tr("&Sort By"));
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
    this->addAction(refresh);

    // Add a separator to the menu
    this->addSeparator();

    // Paste
    QAction *paste = new QAction(QIcon::fromTheme("folder"), "Paste", this);
    paste->setEnabled(false);
    this->addAction(paste);

    // Paste Shortcut
    QAction *pasteShortCut = new QAction(QIcon::fromTheme("folder"), "Paste Shortcut", this);
    pasteShortCut->setEnabled(false);
    this->addAction(pasteShortCut);

    // Add a separator to the menu
    this->addSeparator();

    // New Menu
    QMenu *create = this->addMenu(tr("&New"));

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
    this->addSeparator();

    // Paste
    QAction *desktopSettings = new QAction(QIcon::fromTheme("preferences-desktop"), "Desktop Settings", this);
    desktopSettings->setIconVisibleInMenu(true);
    this->addAction(desktopSettings);

}

// Set Desktop Icons to Large
void QDesktopMenu::setIconsLarge()
{
    qDebug() << "setIconsLarge";
}

// Set Desktop Icons to Large
void QDesktopMenu::setIconsMedium()
{
    qDebug() << "setIconsMedium";
}

// Set Desktop Icons to Large
void QDesktopMenu::setIconsSmall()
{
    qDebug() << "setIconsSmall";
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

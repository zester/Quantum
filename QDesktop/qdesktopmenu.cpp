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

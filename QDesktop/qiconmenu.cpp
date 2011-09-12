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

#include "qiconmenu.h"

QIconMenu::QIconMenu(QWidget *parent) :
    QMenu(parent)
{

    // Create submenu for Create Document
    QMenu *viewMenu = this->addMenu(tr("&View"));

    // Large Icons
    QAction *largeIcons = new QAction(QIcon::fromTheme("folder"), "Large Icons", this);
    largeIcons->setCheckable(true);
    viewMenu->addAction(largeIcons);

    // Medium Icons
    QAction *mediumIcons = new QAction(QIcon::fromTheme("folder"), "Medium Icons", this);
    mediumIcons->setCheckable(true);
    viewMenu->addAction(mediumIcons);

    // Medium Icons
    QAction *smallIcons = new QAction(QIcon::fromTheme("folder"), "Small Icons", this);
    smallIcons->setCheckable(true);
    viewMenu->addAction(smallIcons);

    //
    viewMenu->addSeparator();

    //
    QActionGroup *viewGroup = new QActionGroup(this);
    viewGroup->addAction(largeIcons);
    viewGroup->addAction(mediumIcons);
    viewGroup->addAction(smallIcons);
    mediumIcons->setChecked(true);
}

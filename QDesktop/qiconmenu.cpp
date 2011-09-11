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

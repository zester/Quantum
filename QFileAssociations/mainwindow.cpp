#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QIcon::setThemeName("oxygen");

    setWindowTitle("File Associations");
    setWindowIcon(QIcon::fromTheme("preferences-desktop-filetype-association"));

    QIcon fakeIcon = QIcon::fromTheme("preferences-desktop-filetype-association");
    QPixmap pixmap = fakeIcon.pixmap(QSize(24, 24), QIcon::Normal, QIcon::On);

    ui->label_3->setPixmap(pixmap);
    ui->selectIconButton->setIcon(QIcon::fromTheme("unknown"));
    ui->typeAdd->setIcon(QIcon::fromTheme("add"));
    ui->typeRemove->setIcon(QIcon::fromTheme("remove"));
    ui->helpButton->setIcon(QIcon::fromTheme("help-contents"));
    ui->applyButton->setIcon(QIcon::fromTheme("dialog-ok-apply"));
    ui->resetButton->setIcon(QIcon::fromTheme("edit-undo"));
    ui->defaultsButton->setIcon(QIcon::fromTheme("document-revert"));

    ui->patternsAddButton->setIcon(QIcon::fromTheme("add"));
    ui->patternsRemoveButton->setIcon(QIcon::fromTheme("remove"));

    ui->splitter->setStretchFactor(0, 0);
    ui->splitter->setStretchFactor(1, 1);


    application = new QTreeWidgetItem(ui->treeWidget, QStringList() << "application");
    audio = new QTreeWidgetItem(ui->treeWidget, QStringList() << "audio");
    image = new QTreeWidgetItem(ui->treeWidget, QStringList() << "image");
    inode = new QTreeWidgetItem(ui->treeWidget, QStringList() << "inode");
    message = new QTreeWidgetItem(ui->treeWidget, QStringList() << "message");

    doc = new QDomDocument("mydocument");

    QFile file("/home/steven/Desktop/Chipara/QFileAssociations/freedesktop.org.xml");
    if (!file.open(QIODevice::ReadWrite))
        return;
    if (!doc->setContent(&file)) {
        file.close();
        return;
    }
    file.close();

    QDomElement docElem = doc->documentElement();

    QDomNode n = docElem.firstChild().nextSibling();
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            QString str = e.attribute("type");
            QStringList list = str.split("/");

            qDebug() << list.at(0) << endl; // the node really is an element.
            //qDebug() << list.at(1) << endl; // the node really is an element.

            if (QString::compare("application", list.at(0), Qt::CaseInsensitive) == 0) {
                QTreeWidgetItem *icon;
                icon = new QTreeWidgetItem(application, QStringList() << list.at(1));
                //icon->setIcon(0, QIcon::fromTheme(list.at(1)));
            }

            if (QString::compare("audio", list.at(0), Qt::CaseInsensitive) == 0) {
                QTreeWidgetItem *icon;
                icon = new QTreeWidgetItem(audio, QStringList() << list.at(1));
                //icon->setIcon(0, QIcon::fromTheme(list.at(1)));
            }

            if (QString::compare("image", list.at(0), Qt::CaseInsensitive) == 0) {
                QTreeWidgetItem *icon;
                icon = new QTreeWidgetItem(image, QStringList() << list.at(1));
                //icon->setIcon(0, QIcon::fromTheme(list.at(1)));
            }

            if (QString::compare("inode", list.at(0), Qt::CaseInsensitive) == 0) {
                QTreeWidgetItem *icon;
                icon = new QTreeWidgetItem(inode, QStringList() << list.at(1));
                //icon->setIcon(0, QIcon::fromTheme(list.at(1)));
            }


            if (QString::compare("message", list.at(0), Qt::CaseInsensitive) == 0) {
                QTreeWidgetItem *icon;
                icon = new QTreeWidgetItem(message, QStringList() << list.at(1));
                //icon->setIcon(0, QIcon::fromTheme(list.at(1)));
            }
        }
        n = n.nextSibling();
    }




}

MainWindow::~MainWindow()
{
    delete ui;
}

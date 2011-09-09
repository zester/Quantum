#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtXml>
#include <QTreeWidgetItem>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QDomDocument *doc;
    QTreeWidgetItem *application;
    QTreeWidgetItem *audio;
    QTreeWidgetItem *image;
    QTreeWidgetItem *inode;
    QTreeWidgetItem *message;
};

#endif // MAINWINDOW_H

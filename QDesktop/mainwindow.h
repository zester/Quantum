#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include "qdesktopview.h"
#include <QFileSystemWatcher>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);

    ~MainWindow();

public slots:
    void reloadWallpaper();

private:
    Ui::MainWindow *ui;
    QDesktopViewWidget *desktopView;
    QPixmap wallpaper;
    QSettings *windowSettings;
    QFileSystemWatcher *configFile;
};

#endif // MAINWINDOW_H

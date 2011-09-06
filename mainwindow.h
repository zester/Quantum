#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qdesktopview.h"

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


private:
    Ui::MainWindow *ui;
    QDesktopViewWidget *desktopView;
    QPixmap wallpaper;
};

#endif // MAINWINDOW_H

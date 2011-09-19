#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vlc-qt/Common.h>
#include <vlc-qt/Instance.h>
#include <vlc-qt/MediaPlayer.h>
#include <vlc-qt/VideoWidget.h>
#include <vlc-qt/SeekWidget.h>
#include <vlc-qt/VolumeSlider.h>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void open();

private:
    Ui::MainWindow *ui;
    VlcInstance *instance;
    VlcMediaPlayer *player;

};

#endif // MAINWINDOW_H

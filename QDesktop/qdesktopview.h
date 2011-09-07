#ifndef QDESKTOPVIEWWIDGET_H
#define QDESKTOPVIEWWIDGET_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QMenu>
//#include <QSettings>



class QDesktopViewWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit QDesktopViewWidget(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *);

public slots:
    void iconClicked(QListWidgetItem*);
    void createFolder();
    void createLauncher();
    void createEmptyFile();

private:
    QPoint startPos;
    QMenu *menu;
    QMenu *iconMenu;


signals:


};

#endif // QDESKTOPVIEWWIDGET_H

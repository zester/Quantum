#ifndef QDESKTOPVIEWWIDGET_H
#define QDESKTOPVIEWWIDGET_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QMenu>

class QDesktopViewWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit QDesktopViewWidget(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *);

public slots:
    void iconClicked(QListWidgetItem*);

private:
    QPoint startPos;
    QMenu *menu;
    QMenu *iconMenu;

signals:

public slots:

};

#endif // QDESKTOPVIEWWIDGET_H

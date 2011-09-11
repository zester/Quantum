#ifndef QDESKTOPVIEWITEM_H
#define QDESKTOPVIEWITEM_H

#include <QListWidgetItem>

class QDesktopViewItem : public QListWidgetItem
{
private:
    QString *filename;

public:
    explicit QDesktopViewItem(const QIcon & icon, const QString & text);
    ~QDesktopViewItem();


signals:

public slots:

};

#endif // QDESKTOPVIEWITEM_H

#include "qdesktopviewitem.h"

QDesktopViewItem::QDesktopViewItem(const QIcon &icon, const QString &text) :
    QListWidgetItem(icon, text)
{

}

QDesktopViewItem::~QDesktopViewItem()
{
}

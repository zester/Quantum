/****************************************************************************
** Meta object code from reading C++ file 'qdesktopview.h'
**
** Created: Tue Sep 20 02:18:58 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qdesktopview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qdesktopview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDesktopViewWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      50,   19,   19,   19, 0x0a,
      68,   19,   19,   19, 0x0a,
      87,   19,   19,   19, 0x0a,
     101,   19,   19,   19, 0x0a,
     116,   19,   19,   19, 0x0a,
     133,   19,   19,   19, 0x0a,
     151,   19,   19,   19, 0x0a,
     170,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QDesktopViewWidget[] = {
    "QDesktopViewWidget\0\0iconClicked(QListWidgetItem*)\0"
    "layoutDirection()\0populatedDesktop()\0"
    "resizeIcons()\0createFolder()\0"
    "createLauncher()\0createEmptyFile()\0"
    "showDesktopIcons()\0execDesktopSettings()\0"
};

const QMetaObject QDesktopViewWidget::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata_QDesktopViewWidget,
      qt_meta_data_QDesktopViewWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDesktopViewWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDesktopViewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDesktopViewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDesktopViewWidget))
        return static_cast<void*>(const_cast< QDesktopViewWidget*>(this));
    return QListWidget::qt_metacast(_clname);
}

int QDesktopViewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: iconClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: layoutDirection(); break;
        case 2: populatedDesktop(); break;
        case 3: resizeIcons(); break;
        case 4: createFolder(); break;
        case 5: createLauncher(); break;
        case 6: createEmptyFile(); break;
        case 7: showDesktopIcons(); break;
        case 8: execDesktopSettings(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

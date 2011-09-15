/****************************************************************************
** Meta object code from reading C++ file 'qdesktopmenu.h'
**
** Created: Wed Sep 14 02:56:38 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qdesktopmenu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qdesktopmenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDesktopMenu[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      29,   13,   13,   13, 0x0a,
      46,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QDesktopMenu[] = {
    "QDesktopMenu\0\0createFolder()\0"
    "createLauncher()\0createEmptyFile()\0"
};

const QMetaObject QDesktopMenu::staticMetaObject = {
    { &QMenu::staticMetaObject, qt_meta_stringdata_QDesktopMenu,
      qt_meta_data_QDesktopMenu, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDesktopMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDesktopMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDesktopMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDesktopMenu))
        return static_cast<void*>(const_cast< QDesktopMenu*>(this));
    return QMenu::qt_metacast(_clname);
}

int QDesktopMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: createFolder(); break;
        case 1: createLauncher(); break;
        case 2: createEmptyFile(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

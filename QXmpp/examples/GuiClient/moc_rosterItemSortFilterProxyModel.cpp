/****************************************************************************
** Meta object code from reading C++ file 'rosterItemSortFilterProxyModel.h'
**
** Created: Sun Sep 4 07:31:17 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "rosterItemSortFilterProxyModel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rosterItemSortFilterProxyModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_rosterItemSortFilterProxyModel[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   31,   31,   31, 0x0a,
      61,   31,   31,   31, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_rosterItemSortFilterProxyModel[] = {
    "rosterItemSortFilterProxyModel\0\0"
    "setShowOfflineContacts(bool)\0"
    "sortByName(bool)\0"
};

const QMetaObject rosterItemSortFilterProxyModel::staticMetaObject = {
    { &QSortFilterProxyModel::staticMetaObject, qt_meta_stringdata_rosterItemSortFilterProxyModel,
      qt_meta_data_rosterItemSortFilterProxyModel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &rosterItemSortFilterProxyModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *rosterItemSortFilterProxyModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *rosterItemSortFilterProxyModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_rosterItemSortFilterProxyModel))
        return static_cast<void*>(const_cast< rosterItemSortFilterProxyModel*>(this));
    return QSortFilterProxyModel::qt_metacast(_clname);
}

int rosterItemSortFilterProxyModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSortFilterProxyModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setShowOfflineContacts((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: sortByName((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

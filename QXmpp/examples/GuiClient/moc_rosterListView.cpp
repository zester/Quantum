/****************************************************************************
** Meta object code from reading C++ file 'rosterListView.h'
**
** Created: Sun Sep 4 07:31:17 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "rosterListView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rosterListView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_rosterListView[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   16,   15,   15, 0x05,
      48,   16,   15,   15, 0x05,
      69,   16,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      98,   92,   15,   15, 0x0a,
     124,   92,   15,   15, 0x0a,
     151,   92,   15,   15, 0x0a,
     172,   15,   15,   15, 0x08,
     196,   15,   15,   15, 0x08,
     217,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_rosterListView[] = {
    "rosterListView\0\0bareJid\0showChatDialog(QString)\0"
    "showProfile(QString)\0removeContact(QString)\0"
    "index\0mousePressed(QModelIndex)\0"
    "doubleClicked(QModelIndex)\0"
    "clicked(QModelIndex)\0showChatDialog_helper()\0"
    "showProfile_helper()\0removeContact_helper()\0"
};

const QMetaObject rosterListView::staticMetaObject = {
    { &QListView::staticMetaObject, qt_meta_stringdata_rosterListView,
      qt_meta_data_rosterListView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &rosterListView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *rosterListView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *rosterListView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_rosterListView))
        return static_cast<void*>(const_cast< rosterListView*>(this));
    return QListView::qt_metacast(_clname);
}

int rosterListView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showChatDialog((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: showProfile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: removeContact((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: mousePressed((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: showChatDialog_helper(); break;
        case 7: showProfile_helper(); break;
        case 8: removeContact_helper(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void rosterListView::showChatDialog(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void rosterListView::showProfile(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void rosterListView::removeContact(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE

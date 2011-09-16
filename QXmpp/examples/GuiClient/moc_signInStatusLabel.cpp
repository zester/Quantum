/****************************************************************************
** Meta object code from reading C++ file 'signInStatusLabel.h'
**
** Created: Sun Sep 4 07:31:19 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "signInStatusLabel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'signInStatusLabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_signInStatusLabel[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_signInStatusLabel[] = {
    "signInStatusLabel\0\0timeout()\0"
};

const QMetaObject signInStatusLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_signInStatusLabel,
      qt_meta_data_signInStatusLabel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &signInStatusLabel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *signInStatusLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *signInStatusLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_signInStatusLabel))
        return static_cast<void*>(const_cast< signInStatusLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int signInStatusLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: timeout(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

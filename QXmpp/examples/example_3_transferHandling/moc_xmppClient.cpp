/****************************************************************************
** Meta object code from reading C++ file 'xmppClient.h'
**
** Created: Sun Sep 4 07:30:04 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "xmppClient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xmppClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_xmppClient[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   12,   11,   11, 0x08,
      57,   53,   11,   11, 0x08,
      93,   11,   11,   11, 0x08,
     117,  108,   11,   11, 0x08,
     164,  153,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_xmppClient[] = {
    "xmppClient\0\0error\0slotError(QXmppTransferJob::Error)\0"
    "job\0slotFileReceived(QXmppTransferJob*)\0"
    "slotFinished()\0presence\0"
    "slotPresenceReceived(QXmppPresence)\0"
    "done,total\0slotProgress(qint64,qint64)\0"
};

const QMetaObject xmppClient::staticMetaObject = {
    { &QXmppClient::staticMetaObject, qt_meta_stringdata_xmppClient,
      qt_meta_data_xmppClient, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &xmppClient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *xmppClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *xmppClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_xmppClient))
        return static_cast<void*>(const_cast< xmppClient*>(this));
    return QXmppClient::qt_metacast(_clname);
}

int xmppClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QXmppClient::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotError((*reinterpret_cast< QXmppTransferJob::Error(*)>(_a[1]))); break;
        case 1: slotFileReceived((*reinterpret_cast< QXmppTransferJob*(*)>(_a[1]))); break;
        case 2: slotFinished(); break;
        case 3: slotPresenceReceived((*reinterpret_cast< const QXmppPresence(*)>(_a[1]))); break;
        case 4: slotProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

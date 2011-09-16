/****************************************************************************
** Meta object code from reading C++ file 'statusWidget.h'
**
** Created: Sun Sep 4 07:31:18 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "statusWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'statusWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_statusWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      41,   13,   13,   13, 0x05,
      82,   13,   13,   13, 0x05,
     137,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     159,   13,   13,   13, 0x08,
     183,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_statusWidget[] = {
    "statusWidget\0\0statusTextChanged(QString)\0"
    "presenceTypeChanged(QXmppPresence::Type)\0"
    "presenceStatusTypeChanged(QXmppPresence::Status::Type)\0"
    "avatarChanged(QImage)\0presenceMenuTriggered()\0"
    "avatarSelection()\0"
};

const QMetaObject statusWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_statusWidget,
      qt_meta_data_statusWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &statusWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *statusWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *statusWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_statusWidget))
        return static_cast<void*>(const_cast< statusWidget*>(this));
    if (!strcmp(_clname, "Ui::statusWidgetClass"))
        return static_cast< Ui::statusWidgetClass*>(const_cast< statusWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int statusWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: statusTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: presenceTypeChanged((*reinterpret_cast< QXmppPresence::Type(*)>(_a[1]))); break;
        case 2: presenceStatusTypeChanged((*reinterpret_cast< QXmppPresence::Status::Type(*)>(_a[1]))); break;
        case 3: avatarChanged((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 4: presenceMenuTriggered(); break;
        case 5: avatarSelection(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void statusWidget::statusTextChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void statusWidget::presenceTypeChanged(QXmppPresence::Type _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void statusWidget::presenceStatusTypeChanged(QXmppPresence::Status::Type _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void statusWidget::avatarChanged(const QImage & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE

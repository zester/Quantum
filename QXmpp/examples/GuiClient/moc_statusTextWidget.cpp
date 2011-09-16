/****************************************************************************
** Meta object code from reading C++ file 'statusTextWidget.h'
**
** Created: Sun Sep 4 07:31:20 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "statusTextWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'statusTextWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_statusLineEditButton[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_statusLineEditButton[] = {
    "statusLineEditButton\0"
};

const QMetaObject statusLineEditButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_statusLineEditButton,
      qt_meta_data_statusLineEditButton, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &statusLineEditButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *statusLineEditButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *statusLineEditButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_statusLineEditButton))
        return static_cast<void*>(const_cast< statusLineEditButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int statusLineEditButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_statusTextWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      45,   17,   17,   17, 0x0a,
      56,   17,   17,   17, 0x0a,
      70,   17,   17,   17, 0x08,
      97,   17,   17,   17, 0x08,
     127,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_statusTextWidget[] = {
    "statusTextWidget\0\0statusTextChanged(QString)\0"
    "showMenu()\0textChanged()\0"
    "statusTextChanged_helper()\0"
    "statusTextChanged_menuClick()\0"
    "clearStatusTextHistory()\0"
};

const QMetaObject statusTextWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_statusTextWidget,
      qt_meta_data_statusTextWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &statusTextWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *statusTextWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *statusTextWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_statusTextWidget))
        return static_cast<void*>(const_cast< statusTextWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int statusTextWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: statusTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: showMenu(); break;
        case 2: textChanged(); break;
        case 3: statusTextChanged_helper(); break;
        case 4: statusTextChanged_menuClick(); break;
        case 5: clearStatusTextHistory(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void statusTextWidget::statusTextChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

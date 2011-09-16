/****************************************************************************
** Meta object code from reading C++ file 'mainDialog.h'
**
** Created: Sun Sep 4 07:31:16 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_mainDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      36,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   12,   11,   11, 0x08,
      43,   11,   11,   11, 0x08,
      62,   60,   11,   11, 0x08,
     102,   95,   11,   11, 0x08,
     125,   12,   11,   11, 0x08,
     153,  149,   11,   11, 0x08,
     183,   11,   11,   11, 0x08,
     210,   11,   11,   11, 0x08,
     251,   11,   11,   11, 0x08,
     306,   11,   11,   11, 0x08,
     315,   11,   11,   11, 0x08,
     330,   11,   11,   11, 0x08,
     347,   11,   11,   11, 0x08,
     386,   11,   11,   11, 0x08,
     425,   11,   11,   11, 0x08,
     464,   11,   11,   11, 0x08,
     481,   11,   11,   11, 0x08,
     499,   11,   11,   11, 0x08,
     520,  149,   11,   11, 0x08,
     557,  149,   11,   11, 0x08,
     591,  582,   11,   11, 0x08,
     631,   12,   11,   11, 0x08,
     652,   11,   11,   11, 0x08,
     674,   12,   11,   11, 0x08,
     695,   11,   11,   11, 0x08,
     732,   11,   11,   11, 0x08,
     752,   11,   11,   11, 0x08,
     784,   11,   11,   11, 0x08,
     816,   11,   11,   11, 0x08,
     836,   12,   11,   11, 0x08,
     866,   11,   11,   11, 0x08,
     883,   11,   11,   11, 0x08,
     904,  897,   11,   11, 0x08,
     964,   11,   11,   11, 0x08,
     981,   11,   11,   11, 0x08,
     999,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_mainDialog[] = {
    "mainDialog\0\0bareJid\0rosterChanged(QString)\0"
    "rosterReceived()\0,\0presenceChanged(QString,QString)\0"
    "filter\0filterChanged(QString)\0"
    "showChatDialog(QString)\0msg\0"
    "messageReceived(QXmppMessage)\0"
    "statusTextChanged(QString)\0"
    "presenceTypeChanged(QXmppPresence::Type)\0"
    "presenceStatusTypeChanged(QXmppPresence::Status::Type)\0"
    "signIn()\0cancelSignIn()\0showSignInPage()\0"
    "showSignInPageAfterUserDisconnection()\0"
    "showSignInPageForAutoReconnection(int)\0"
    "showSignInPageForAutoReconnectionNow()\0"
    "showRosterPage()\0startConnection()\0"
    "updateStatusWidget()\0"
    "showLoginStatusWithProgress(QString)\0"
    "showLoginStatus(QString)\0msg,time\0"
    "showLoginStatusWithCounter(QString,int)\0"
    "updateVCard(QString)\0avatarChanged(QImage)\0"
    "showProfile(QString)\0"
    "userNameCompleter_activated(QString)\0"
    "addAccountToCache()\0presenceReceived(QXmppPresence)\0"
    "errorClient(QXmppClient::Error)\0"
    "action_addContact()\0action_removeContact(QString)\0"
    "action_signOut()\0action_quit()\0reason\0"
    "action_trayIconActivated(QSystemTrayIcon::ActivationReason)\0"
    "action_showXml()\0action_aboutDlg()\0"
    "action_settingsPressed()\0"
};

const QMetaObject mainDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_mainDialog,
      qt_meta_data_mainDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &mainDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *mainDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *mainDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mainDialog))
        return static_cast<void*>(const_cast< mainDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int mainDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: rosterChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: rosterReceived(); break;
        case 2: presenceChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: filterChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: showChatDialog((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: messageReceived((*reinterpret_cast< const QXmppMessage(*)>(_a[1]))); break;
        case 6: statusTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: presenceTypeChanged((*reinterpret_cast< QXmppPresence::Type(*)>(_a[1]))); break;
        case 8: presenceStatusTypeChanged((*reinterpret_cast< QXmppPresence::Status::Type(*)>(_a[1]))); break;
        case 9: signIn(); break;
        case 10: cancelSignIn(); break;
        case 11: showSignInPage(); break;
        case 12: showSignInPageAfterUserDisconnection(); break;
        case 13: showSignInPageForAutoReconnection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: showSignInPageForAutoReconnectionNow(); break;
        case 15: showRosterPage(); break;
        case 16: startConnection(); break;
        case 17: updateStatusWidget(); break;
        case 18: showLoginStatusWithProgress((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 19: showLoginStatus((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 20: showLoginStatusWithCounter((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 21: updateVCard((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 22: avatarChanged((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 23: showProfile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 24: userNameCompleter_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 25: addAccountToCache(); break;
        case 26: presenceReceived((*reinterpret_cast< const QXmppPresence(*)>(_a[1]))); break;
        case 27: errorClient((*reinterpret_cast< QXmppClient::Error(*)>(_a[1]))); break;
        case 28: action_addContact(); break;
        case 29: action_removeContact((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 30: action_signOut(); break;
        case 31: action_quit(); break;
        case 32: action_trayIconActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 33: action_showXml(); break;
        case 34: action_aboutDlg(); break;
        case 35: action_settingsPressed(); break;
        default: ;
        }
        _id -= 36;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

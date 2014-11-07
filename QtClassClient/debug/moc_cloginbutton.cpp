/****************************************************************************
** Meta object code from reading C++ file 'cloginbutton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../UserInterface/cloginbutton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cloginbutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CLoginButton_t {
    QByteArrayData data[11];
    char stringdata[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CLoginButton_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CLoginButton_t qt_meta_stringdata_CLoginButton = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 12),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 8),
QT_MOC_LITERAL(4, 36, 8),
QT_MOC_LITERAL(5, 45, 13),
QT_MOC_LITERAL(6, 59, 10),
QT_MOC_LITERAL(7, 70, 13),
QT_MOC_LITERAL(8, 84, 4),
QT_MOC_LITERAL(9, 89, 9),
QT_MOC_LITERAL(10, 99, 5)
    },
    "CLoginButton\0loginClicked\0\0username\0"
    "password\0logoutClicked\0sendPrompt\0"
    "usernameCheck\0text\0stopTimer\0login"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CLoginButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       5,    0,   49,    2, 0x06 /* Public */,
       6,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   53,    2, 0x0a /* Public */,
       9,    0,   56,    2, 0x0a /* Public */,
      10,    0,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CLoginButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CLoginButton *_t = static_cast<CLoginButton *>(_o);
        switch (_id) {
        case 0: _t->loginClicked((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->logoutClicked(); break;
        case 2: _t->sendPrompt((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->usernameCheck((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->stopTimer(); break;
        case 5: _t->login(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CLoginButton::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CLoginButton::loginClicked)) {
                *result = 0;
            }
        }
        {
            typedef void (CLoginButton::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CLoginButton::logoutClicked)) {
                *result = 1;
            }
        }
        {
            typedef void (CLoginButton::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CLoginButton::sendPrompt)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject CLoginButton::staticMetaObject = {
    { &QToolButton::staticMetaObject, qt_meta_stringdata_CLoginButton.data,
      qt_meta_data_CLoginButton,  qt_static_metacall, 0, 0}
};


const QMetaObject *CLoginButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CLoginButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CLoginButton.stringdata))
        return static_cast<void*>(const_cast< CLoginButton*>(this));
    return QToolButton::qt_metacast(_clname);
}

int CLoginButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CLoginButton::loginClicked(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CLoginButton::logoutClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void CLoginButton::sendPrompt(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE

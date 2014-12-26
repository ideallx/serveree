/****************************************************************************
** Meta object code from reading C++ file 'logindialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../BeforeClass/logindialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logindialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LoginDialog_t {
    QByteArrayData data[20];
    char stringdata[263];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LoginDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LoginDialog_t qt_meta_stringdata_LoginDialog = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 10),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 8),
QT_MOC_LITERAL(4, 33, 8),
QT_MOC_LITERAL(5, 42, 12),
QT_MOC_LITERAL(6, 55, 8),
QT_MOC_LITERAL(7, 64, 13),
QT_MOC_LITERAL(8, 78, 6),
QT_MOC_LITERAL(9, 85, 11),
QT_MOC_LITERAL(10, 97, 9),
QT_MOC_LITERAL(11, 107, 15),
QT_MOC_LITERAL(12, 123, 5),
QT_MOC_LITERAL(13, 129, 23),
QT_MOC_LITERAL(14, 153, 17),
QT_MOC_LITERAL(15, 171, 14),
QT_MOC_LITERAL(16, 186, 25),
QT_MOC_LITERAL(17, 212, 4),
QT_MOC_LITERAL(18, 217, 25),
QT_MOC_LITERAL(19, 243, 19)
    },
    "LoginDialog\0loginClass\0\0username\0"
    "password\0loginSuccess\0endTimer\0"
    "promptChanged\0result\0classReview\0"
    "className\0progressChanged\0value\0"
    "on_tbEnterClass_clicked\0on_tbExit_clicked\0"
    "sendNoResponse\0on_leUsername_textChanged\0"
    "arg1\0on_lePassword_textChanged\0"
    "on_tbReplay_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LoginDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x06 /* Public */,
       5,    0,   79,    2, 0x06 /* Public */,
       6,    0,   80,    2, 0x06 /* Public */,
       7,    1,   81,    2, 0x06 /* Public */,
       9,    1,   84,    2, 0x06 /* Public */,
      11,    1,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,
      15,    0,   92,    2, 0x08 /* Private */,
      16,    1,   93,    2, 0x08 /* Private */,
      18,    1,   96,    2, 0x08 /* Private */,
      19,    0,   99,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::Int,   12,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void,

       0        // eod
};

void LoginDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LoginDialog *_t = static_cast<LoginDialog *>(_o);
        switch (_id) {
        case 0: _t->loginClass((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->loginSuccess(); break;
        case 2: _t->endTimer(); break;
        case 3: _t->promptChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->classReview((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->progressChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_tbEnterClass_clicked(); break;
        case 7: _t->on_tbExit_clicked(); break;
        case 8: _t->sendNoResponse(); break;
        case 9: _t->on_leUsername_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->on_lePassword_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->on_tbReplay_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LoginDialog::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LoginDialog::loginClass)) {
                *result = 0;
            }
        }
        {
            typedef void (LoginDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LoginDialog::loginSuccess)) {
                *result = 1;
            }
        }
        {
            typedef void (LoginDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LoginDialog::endTimer)) {
                *result = 2;
            }
        }
        {
            typedef void (LoginDialog::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LoginDialog::promptChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (LoginDialog::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LoginDialog::classReview)) {
                *result = 4;
            }
        }
        {
            typedef void (LoginDialog::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LoginDialog::progressChanged)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject LoginDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_LoginDialog.data,
      qt_meta_data_LoginDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *LoginDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoginDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoginDialog.stringdata))
        return static_cast<void*>(const_cast< LoginDialog*>(this));
    if (!strcmp(_clname, "CMsgObject"))
        return static_cast< CMsgObject*>(const_cast< LoginDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int LoginDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void LoginDialog::loginClass(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LoginDialog::loginSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void LoginDialog::endTimer()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void LoginDialog::promptChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void LoginDialog::classReview(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void LoginDialog::progressChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE

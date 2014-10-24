/****************************************************************************
** Meta object code from reading C++ file 'tst_cserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../UnitTest/tst_cserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tst_cserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tst_CServer_t {
    QByteArrayData data[13];
    char stringdata[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tst_CServer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tst_CServer_t qt_meta_stringdata_tst_CServer = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 12),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 15),
QT_MOC_LITERAL(4, 42, 4),
QT_MOC_LITERAL(5, 47, 7),
QT_MOC_LITERAL(6, 55, 10),
QT_MOC_LITERAL(7, 66, 14),
QT_MOC_LITERAL(8, 81, 14),
QT_MOC_LITERAL(9, 96, 14),
QT_MOC_LITERAL(10, 111, 14),
QT_MOC_LITERAL(11, 126, 14),
QT_MOC_LITERAL(12, 141, 15)
    },
    "tst_CServer\0initTestCase\0\0cleanupTestCase\0"
    "init\0cleanup\0workserver\0run1ClientEasy\0"
    "run1ClientHard\0run2ClientHard\0"
    "run5ClientEasy\0run5ClientHard\0"
    "run10ClientEasy"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tst_CServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void tst_CServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tst_CServer *_t = static_cast<tst_CServer *>(_o);
        switch (_id) {
        case 0: _t->initTestCase(); break;
        case 1: _t->cleanupTestCase(); break;
        case 2: _t->init(); break;
        case 3: _t->cleanup(); break;
        case 4: _t->workserver(); break;
        case 5: _t->run1ClientEasy(); break;
        case 6: _t->run1ClientHard(); break;
        case 7: _t->run2ClientHard(); break;
        case 8: _t->run5ClientEasy(); break;
        case 9: _t->run5ClientHard(); break;
        case 10: _t->run10ClientEasy(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject tst_CServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_tst_CServer.data,
      qt_meta_data_tst_CServer,  qt_static_metacall, 0, 0}
};


const QMetaObject *tst_CServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tst_CServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tst_CServer.stringdata))
        return static_cast<void*>(const_cast< tst_CServer*>(this));
    return QObject::qt_metacast(_clname);
}

int tst_CServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

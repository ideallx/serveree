/****************************************************************************
** Meta object code from reading C++ file 'tst_cagentserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtClassUnitTest/UnitTest/tst_cagentserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tst_cagentserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tst_CAgentServer_t {
    QByteArrayData data[12];
    char stringdata[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tst_CAgentServer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tst_CAgentServer_t qt_meta_stringdata_tst_CAgentServer = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 12),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 15),
QT_MOC_LITERAL(4, 47, 4),
QT_MOC_LITERAL(5, 52, 7),
QT_MOC_LITERAL(6, 60, 10),
QT_MOC_LITERAL(7, 71, 10),
QT_MOC_LITERAL(8, 82, 11),
QT_MOC_LITERAL(9, 94, 12),
QT_MOC_LITERAL(10, 107, 9),
QT_MOC_LITERAL(11, 117, 11)
    },
    "tst_CAgentServer\0initTestCase\0\0"
    "cleanupTestCase\0init\0cleanup\0enterclass\0"
    "leaveclass\0createclass\0destroyclass\0"
    "heartbeat\0halfwayUser"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tst_CAgentServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

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

       0        // eod
};

void tst_CAgentServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tst_CAgentServer *_t = static_cast<tst_CAgentServer *>(_o);
        switch (_id) {
        case 0: _t->initTestCase(); break;
        case 1: _t->cleanupTestCase(); break;
        case 2: _t->init(); break;
        case 3: _t->cleanup(); break;
        case 4: _t->enterclass(); break;
        case 5: _t->leaveclass(); break;
        case 6: _t->createclass(); break;
        case 7: _t->destroyclass(); break;
        case 8: _t->heartbeat(); break;
        case 9: _t->halfwayUser(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject tst_CAgentServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_tst_CAgentServer.data,
      qt_meta_data_tst_CAgentServer,  qt_static_metacall, 0, 0}
};


const QMetaObject *tst_CAgentServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tst_CAgentServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tst_CAgentServer.stringdata))
        return static_cast<void*>(const_cast< tst_CAgentServer*>(this));
    return QObject::qt_metacast(_clname);
}

int tst_CAgentServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

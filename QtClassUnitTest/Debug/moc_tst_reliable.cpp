/****************************************************************************
** Meta object code from reading C++ file 'tst_reliable.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../UnitTest/tst_reliable.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tst_reliable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tst_Reliable_t {
    QByteArrayData data[10];
    char stringdata[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tst_Reliable_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tst_Reliable_t qt_meta_stringdata_tst_Reliable = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 12),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 15),
QT_MOC_LITERAL(4, 43, 10),
QT_MOC_LITERAL(5, 54, 4),
QT_MOC_LITERAL(6, 59, 11),
QT_MOC_LITERAL(7, 71, 14),
QT_MOC_LITERAL(8, 86, 4),
QT_MOC_LITERAL(9, 91, 7)
    },
    "tst_Reliable\0initTestCase\0\0cleanupTestCase\0"
    "connection\0recv\0missingRate\0resendFragment\0"
    "init\0cleanup"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tst_Reliable[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
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

void tst_Reliable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tst_Reliable *_t = static_cast<tst_Reliable *>(_o);
        switch (_id) {
        case 0: _t->initTestCase(); break;
        case 1: _t->cleanupTestCase(); break;
        case 2: _t->connection(); break;
        case 3: _t->recv(); break;
        case 4: _t->missingRate(); break;
        case 5: _t->resendFragment(); break;
        case 6: _t->init(); break;
        case 7: _t->cleanup(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject tst_Reliable::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_tst_Reliable.data,
      qt_meta_data_tst_Reliable,  qt_static_metacall, 0, 0}
};


const QMetaObject *tst_Reliable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tst_Reliable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tst_Reliable.stringdata))
        return static_cast<void*>(const_cast< tst_Reliable*>(this));
    return QObject::qt_metacast(_clname);
}

int tst_Reliable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

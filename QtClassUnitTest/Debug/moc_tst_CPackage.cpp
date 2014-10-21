/****************************************************************************
** Meta object code from reading C++ file 'tst_CPackage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../UnitTest/tst_CPackage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tst_CPackage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tst_CPackage_t {
    QByteArrayData data[19];
    char stringdata[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tst_CPackage_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tst_CPackage_t qt_meta_stringdata_tst_CPackage = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 12),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 15),
QT_MOC_LITERAL(4, 43, 11),
QT_MOC_LITERAL(5, 55, 11),
QT_MOC_LITERAL(6, 67, 11),
QT_MOC_LITERAL(7, 79, 10),
QT_MOC_LITERAL(8, 90, 10),
QT_MOC_LITERAL(9, 101, 8),
QT_MOC_LITERAL(10, 110, 8),
QT_MOC_LITERAL(11, 119, 11),
QT_MOC_LITERAL(12, 131, 11),
QT_MOC_LITERAL(13, 143, 11),
QT_MOC_LITERAL(14, 155, 11),
QT_MOC_LITERAL(15, 167, 22),
QT_MOC_LITERAL(16, 190, 23),
QT_MOC_LITERAL(17, 214, 4),
QT_MOC_LITERAL(18, 219, 7)
    },
    "tst_CPackage\0initTestCase\0\0cleanupTestCase\0"
    "testInsert1\0testInsert2\0testInsert3\0"
    "testQuery1\0testQuery2\0testSave\0testLoad\0"
    "testIsExist\0testIsFull1\0testIsFull2\0"
    "testScanAll\0testScanMissingPackets\0"
    "testScanMissingPackets2\0init\0cleanup"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tst_CPackage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x08 /* Private */,
       3,    0,  100,    2, 0x08 /* Private */,
       4,    0,  101,    2, 0x08 /* Private */,
       5,    0,  102,    2, 0x08 /* Private */,
       6,    0,  103,    2, 0x08 /* Private */,
       7,    0,  104,    2, 0x08 /* Private */,
       8,    0,  105,    2, 0x08 /* Private */,
       9,    0,  106,    2, 0x08 /* Private */,
      10,    0,  107,    2, 0x08 /* Private */,
      11,    0,  108,    2, 0x08 /* Private */,
      12,    0,  109,    2, 0x08 /* Private */,
      13,    0,  110,    2, 0x08 /* Private */,
      14,    0,  111,    2, 0x08 /* Private */,
      15,    0,  112,    2, 0x08 /* Private */,
      16,    0,  113,    2, 0x08 /* Private */,
      17,    0,  114,    2, 0x08 /* Private */,
      18,    0,  115,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void tst_CPackage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tst_CPackage *_t = static_cast<tst_CPackage *>(_o);
        switch (_id) {
        case 0: _t->initTestCase(); break;
        case 1: _t->cleanupTestCase(); break;
        case 2: _t->testInsert1(); break;
        case 3: _t->testInsert2(); break;
        case 4: _t->testInsert3(); break;
        case 5: _t->testQuery1(); break;
        case 6: _t->testQuery2(); break;
        case 7: _t->testSave(); break;
        case 8: _t->testLoad(); break;
        case 9: _t->testIsExist(); break;
        case 10: _t->testIsFull1(); break;
        case 11: _t->testIsFull2(); break;
        case 12: _t->testScanAll(); break;
        case 13: _t->testScanMissingPackets(); break;
        case 14: _t->testScanMissingPackets2(); break;
        case 15: _t->init(); break;
        case 16: _t->cleanup(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject tst_CPackage::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_tst_CPackage.data,
      qt_meta_data_tst_CPackage,  qt_static_metacall, 0, 0}
};


const QMetaObject *tst_CPackage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tst_CPackage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tst_CPackage.stringdata))
        return static_cast<void*>(const_cast< tst_CPackage*>(this));
    return QObject::qt_metacast(_clname);
}

int tst_CPackage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

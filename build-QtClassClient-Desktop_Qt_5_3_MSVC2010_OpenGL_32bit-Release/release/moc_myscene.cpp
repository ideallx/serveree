/****************************************************************************
** Meta object code from reading C++ file 'myscene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtClassClient/LayerUI/DrawingScreen/myscene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MyScene_t {
    QByteArrayData data[19];
    char stringdata[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyScene_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyScene_t qt_meta_stringdata_MyScene = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 15),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 5),
QT_MOC_LITERAL(4, 31, 11),
QT_MOC_LITERAL(5, 43, 5),
QT_MOC_LITERAL(6, 49, 11),
QT_MOC_LITERAL(7, 61, 1),
QT_MOC_LITERAL(8, 63, 13),
QT_MOC_LITERAL(9, 77, 17),
QT_MOC_LITERAL(10, 95, 18),
QT_MOC_LITERAL(11, 114, 10),
QT_MOC_LITERAL(12, 125, 3),
QT_MOC_LITERAL(13, 129, 13),
QT_MOC_LITERAL(14, 143, 10),
QT_MOC_LITERAL(15, 154, 9),
QT_MOC_LITERAL(16, 164, 3),
QT_MOC_LITERAL(17, 168, 10),
QT_MOC_LITERAL(18, 179, 1)
    },
    "MyScene\0changeShapeByUI\0\0shape\0"
    "setPenWidth\0width\0setPenColor\0c\0"
    "setBrushColor\0setOthersPenBrush\0"
    "TS_GRAPHIC_PACKET&\0graphicMsg\0cls\0"
    "sendMoveBegin\0revocation\0setEraser\0"
    "set\0moveScreen\0p"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyScene[] = {

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
       1,    1,   64,    2, 0x0a /* Public */,
       4,    1,   67,    2, 0x0a /* Public */,
       6,    1,   70,    2, 0x0a /* Public */,
       8,    1,   73,    2, 0x0a /* Public */,
       9,    1,   76,    2, 0x0a /* Public */,
      12,    0,   79,    2, 0x0a /* Public */,
      13,    0,   80,    2, 0x0a /* Public */,
      14,    0,   81,    2, 0x0a /* Public */,
      15,    1,   82,    2, 0x0a /* Public */,
      17,    1,   85,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::QColor,    7,
    QMetaType::Void, QMetaType::QColor,    7,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, QMetaType::QPoint,   18,

       0        // eod
};

void MyScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyScene *_t = static_cast<MyScene *>(_o);
        switch (_id) {
        case 0: _t->changeShapeByUI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setPenWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setPenColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 3: _t->setBrushColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 4: _t->setOthersPenBrush((*reinterpret_cast< TS_GRAPHIC_PACKET(*)>(_a[1]))); break;
        case 5: _t->cls(); break;
        case 6: _t->sendMoveBegin(); break;
        case 7: _t->revocation(); break;
        case 8: _t->setEraser((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->moveScreen((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MyScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_MyScene.data,
      qt_meta_data_MyScene,  qt_static_metacall, 0, 0}
};


const QMetaObject *MyScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyScene::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyScene.stringdata))
        return static_cast<void*>(const_cast< MyScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int MyScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
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

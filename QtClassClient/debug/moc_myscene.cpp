/****************************************************************************
** Meta object code from reading C++ file 'myscene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../LayerUI/DrawingScreen/myscene.h"
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
    QByteArrayData data[21];
    char stringdata[210];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyScene_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyScene_t qt_meta_stringdata_MyScene = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 10),
QT_MOC_LITERAL(2, 19, 0),
QT_MOC_LITERAL(3, 20, 17),
QT_MOC_LITERAL(4, 38, 15),
QT_MOC_LITERAL(5, 54, 5),
QT_MOC_LITERAL(6, 60, 11),
QT_MOC_LITERAL(7, 72, 5),
QT_MOC_LITERAL(8, 78, 11),
QT_MOC_LITERAL(9, 90, 1),
QT_MOC_LITERAL(10, 92, 13),
QT_MOC_LITERAL(11, 106, 17),
QT_MOC_LITERAL(12, 124, 18),
QT_MOC_LITERAL(13, 143, 10),
QT_MOC_LITERAL(14, 154, 3),
QT_MOC_LITERAL(15, 158, 13),
QT_MOC_LITERAL(16, 172, 10),
QT_MOC_LITERAL(17, 183, 9),
QT_MOC_LITERAL(18, 193, 3),
QT_MOC_LITERAL(19, 197, 10),
QT_MOC_LITERAL(20, 208, 1)
    },
    "MyScene\0changeSide\0\0isCoursewareSlide\0"
    "changeShapeByUI\0shape\0setPenWidth\0"
    "width\0setPenColor\0c\0setBrushColor\0"
    "setOthersPenBrush\0TS_GRAPHIC_PACKET&\0"
    "graphicMsg\0cls\0sendMoveBegin\0revocation\0"
    "setEraser\0set\0moveScreen\0p"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyScene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   72,    2, 0x0a /* Public */,
       6,    1,   75,    2, 0x0a /* Public */,
       8,    1,   78,    2, 0x0a /* Public */,
      10,    1,   81,    2, 0x0a /* Public */,
      11,    1,   84,    2, 0x0a /* Public */,
      14,    0,   87,    2, 0x0a /* Public */,
      15,    0,   88,    2, 0x0a /* Public */,
      16,    0,   89,    2, 0x0a /* Public */,
      17,    1,   90,    2, 0x0a /* Public */,
      19,    1,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::QColor,    9,
    QMetaType::Void, QMetaType::QColor,    9,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::QPoint,   20,

       0        // eod
};

void MyScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyScene *_t = static_cast<MyScene *>(_o);
        switch (_id) {
        case 0: _t->changeSide((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->changeShapeByUI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setPenWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setPenColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 4: _t->setBrushColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 5: _t->setOthersPenBrush((*reinterpret_cast< TS_GRAPHIC_PACKET(*)>(_a[1]))); break;
        case 6: _t->cls(); break;
        case 7: _t->sendMoveBegin(); break;
        case 8: _t->revocation(); break;
        case 9: _t->setEraser((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->moveScreen((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MyScene::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyScene::changeSide)) {
                *result = 0;
            }
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

// SIGNAL 0
void MyScene::changeSide(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

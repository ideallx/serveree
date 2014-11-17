/****************************************************************************
** Meta object code from reading C++ file 'cshapechooser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../UserInterface/cshapechooser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cshapechooser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CShapeChooser_t {
    QByteArrayData data[5];
    char stringdata[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CShapeChooser_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CShapeChooser_t qt_meta_stringdata_CShapeChooser = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 18),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 9),
QT_MOC_LITERAL(4, 44, 13)
    },
    "CShapeChooser\0signalShapeChanged\0\0"
    "shapeType\0onTypeChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CShapeChooser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   27,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void CShapeChooser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CShapeChooser *_t = static_cast<CShapeChooser *>(_o);
        switch (_id) {
        case 0: _t->signalShapeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onTypeChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CShapeChooser::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CShapeChooser::signalShapeChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject CShapeChooser::staticMetaObject = {
    { &QToolButton::staticMetaObject, qt_meta_stringdata_CShapeChooser.data,
      qt_meta_data_CShapeChooser,  qt_static_metacall, 0, 0}
};


const QMetaObject *CShapeChooser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CShapeChooser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CShapeChooser.stringdata))
        return static_cast<void*>(const_cast< CShapeChooser*>(this));
    return QToolButton::qt_metacast(_clname);
}

int CShapeChooser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CShapeChooser::signalShapeChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

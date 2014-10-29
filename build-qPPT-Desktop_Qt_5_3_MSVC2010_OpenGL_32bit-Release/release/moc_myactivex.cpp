/****************************************************************************
** Meta object code from reading C++ file 'myactivex.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qPPT/myactivex.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myactivex.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MyActiveX_t {
    QByteArrayData data[12];
    char stringdata[196];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyActiveX_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyActiveX_t qt_meta_stringdata_MyActiveX = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 7),
QT_MOC_LITERAL(2, 18, 3),
QT_MOC_LITERAL(3, 22, 7),
QT_MOC_LITERAL(4, 30, 38),
QT_MOC_LITERAL(5, 69, 11),
QT_MOC_LITERAL(6, 81, 38),
QT_MOC_LITERAL(7, 120, 8),
QT_MOC_LITERAL(8, 129, 38),
QT_MOC_LITERAL(9, 168, 10),
QT_MOC_LITERAL(10, 179, 3),
QT_MOC_LITERAL(11, 183, 12)
    },
    "MyActiveX\0Version\0""2.0\0ClassID\0"
    "{7a4cffd8-cbcd-4ae9-ae7e-343e1e5710df}\0"
    "InterfaceID\0{6fb035bf-8019-48d8-be51-ef05427d8994}\0"
    "EventsID\0{c42fffdf-6557-47c9-817a-2da2228bc29c}\0"
    "Insertable\0yes\0ToSuperClass"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyActiveX[] = {

 // content:
       7,       // revision
       0,       // classname
       6,   14, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    6,
       7,    8,
       9,   10,
      11,    0,

       0        // eod
};

void MyActiveX::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject MyActiveX::staticMetaObject = {
    { &QAxWidget::staticMetaObject, qt_meta_stringdata_MyActiveX.data,
      qt_meta_data_MyActiveX,  qt_static_metacall, 0, 0}
};


const QMetaObject *MyActiveX::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyActiveX::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyActiveX.stringdata))
        return static_cast<void*>(const_cast< MyActiveX*>(this));
    return QAxWidget::qt_metacast(_clname);
}

int MyActiveX::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAxWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE

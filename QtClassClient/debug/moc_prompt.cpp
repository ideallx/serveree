/****************************************************************************
** Meta object code from reading C++ file 'prompt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../LayerUI/UserInterface/prompt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'prompt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Prompt_t {
    QByteArrayData data[6];
    char stringdata[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Prompt_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Prompt_t qt_meta_stringdata_Prompt = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 15),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 5),
QT_MOC_LITERAL(4, 30, 20),
QT_MOC_LITERAL(5, 51, 19)
    },
    "Prompt\0progressChanged\0\0value\0"
    "on_pbConfirm_clicked\0on_pbCancel_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Prompt[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   32,    2, 0x08 /* Private */,
       5,    0,   33,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Prompt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Prompt *_t = static_cast<Prompt *>(_o);
        switch (_id) {
        case 0: _t->progressChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_pbConfirm_clicked(); break;
        case 2: _t->on_pbCancel_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Prompt::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Prompt::progressChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Prompt::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Prompt.data,
      qt_meta_data_Prompt,  qt_static_metacall, 0, 0}
};


const QMetaObject *Prompt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Prompt::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Prompt.stringdata))
        return static_cast<void*>(const_cast< Prompt*>(this));
    return QDialog::qt_metacast(_clname);
}

int Prompt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Prompt::progressChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

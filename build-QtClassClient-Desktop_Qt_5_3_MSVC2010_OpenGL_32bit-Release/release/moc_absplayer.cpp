/****************************************************************************
** Meta object code from reading C++ file 'absplayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtClassClient/player/absplayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'absplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AbsPlayer_t {
    QByteArrayData data[8];
    char stringdata[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AbsPlayer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AbsPlayer_t qt_meta_stringdata_AbsPlayer = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 9),
QT_MOC_LITERAL(2, 20, 0),
QT_MOC_LITERAL(3, 21, 17),
QT_MOC_LITERAL(4, 39, 9),
QT_MOC_LITERAL(5, 49, 13),
QT_MOC_LITERAL(6, 63, 10),
QT_MOC_LITERAL(7, 74, 6)
    },
    "AbsPlayer\0playerEnd\0\0backgroundChanged\0"
    "playMedia\0QMediaPlayer*\0promptSent\0"
    "prompt"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AbsPlayer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    1,   35,    2, 0x06 /* Public */,
       4,    1,   38,    2, 0x06 /* Public */,
       6,    1,   41,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

void AbsPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AbsPlayer *_t = static_cast<AbsPlayer *>(_o);
        switch (_id) {
        case 0: _t->playerEnd(); break;
        case 1: _t->backgroundChanged((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 2: _t->playMedia((*reinterpret_cast< QMediaPlayer*(*)>(_a[1]))); break;
        case 3: _t->promptSent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaPlayer* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AbsPlayer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbsPlayer::playerEnd)) {
                *result = 0;
            }
        }
        {
            typedef void (AbsPlayer::*_t)(QPixmap );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbsPlayer::backgroundChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (AbsPlayer::*_t)(QMediaPlayer * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbsPlayer::playMedia)) {
                *result = 2;
            }
        }
        {
            typedef void (AbsPlayer::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbsPlayer::promptSent)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject AbsPlayer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AbsPlayer.data,
      qt_meta_data_AbsPlayer,  qt_static_metacall, 0, 0}
};


const QMetaObject *AbsPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AbsPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AbsPlayer.stringdata))
        return static_cast<void*>(const_cast< AbsPlayer*>(this));
    return QObject::qt_metacast(_clname);
}

int AbsPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void AbsPlayer::playerEnd()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void AbsPlayer::backgroundChanged(QPixmap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AbsPlayer::playMedia(QMediaPlayer * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AbsPlayer::promptSent(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE

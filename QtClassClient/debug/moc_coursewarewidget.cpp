/****************************************************************************
** Meta object code from reading C++ file 'coursewarewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../LayerUI/SlideScreen/coursewarewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'coursewarewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CourseWareWidget_t {
    QByteArrayData data[27];
    char stringdata[365];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CourseWareWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CourseWareWidget_t qt_meta_stringdata_CourseWareWidget = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 11),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 9),
QT_MOC_LITERAL(4, 40, 7),
QT_MOC_LITERAL(5, 48, 11),
QT_MOC_LITERAL(6, 60, 16),
QT_MOC_LITERAL(7, 77, 4),
QT_MOC_LITERAL(8, 82, 10),
QT_MOC_LITERAL(9, 93, 6),
QT_MOC_LITERAL(10, 100, 16),
QT_MOC_LITERAL(11, 117, 3),
QT_MOC_LITERAL(12, 121, 11),
QT_MOC_LITERAL(13, 133, 13),
QT_MOC_LITERAL(14, 147, 6),
QT_MOC_LITERAL(15, 154, 18),
QT_MOC_LITERAL(16, 173, 17),
QT_MOC_LITERAL(17, 191, 17),
QT_MOC_LITERAL(18, 209, 19),
QT_MOC_LITERAL(19, 229, 17),
QT_MOC_LITERAL(20, 247, 28),
QT_MOC_LITERAL(21, 276, 16),
QT_MOC_LITERAL(22, 293, 7),
QT_MOC_LITERAL(23, 301, 8),
QT_MOC_LITERAL(24, 310, 21),
QT_MOC_LITERAL(25, 332, 27),
QT_MOC_LITERAL(26, 360, 4)
    },
    "CourseWareWidget\0clearScreen\0\0TS_UINT64\0"
    "sceneID\0cleanOption\0paintModeChanged\0"
    "mode\0promptSent\0result\0changeBackground\0"
    "pic\0changeMedia\0QMediaPlayer*\0player\0"
    "on_tbStart_clicked\0on_tbPrev_clicked\0"
    "on_tbNext_clicked\0on_tbUpload_clicked\0"
    "on_tbSync_clicked\0on_lsWare_currentItemChanged\0"
    "QListWidgetItem*\0current\0previous\0"
    "on_tbExitWare_clicked\0on_lsWare_itemDoubleClicked\0"
    "item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CourseWareWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   79,    2, 0x06 /* Public */,
       6,    1,   84,    2, 0x06 /* Public */,
       8,    1,   87,    2, 0x06 /* Public */,
      10,    1,   90,    2, 0x06 /* Public */,
      12,    1,   93,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    0,   96,    2, 0x08 /* Private */,
      16,    0,   97,    2, 0x08 /* Private */,
      17,    0,   98,    2, 0x08 /* Private */,
      18,    0,   99,    2, 0x08 /* Private */,
      19,    0,  100,    2, 0x08 /* Private */,
      20,    2,  101,    2, 0x08 /* Private */,
      24,    0,  106,    2, 0x08 /* Private */,
      25,    1,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::QPixmap,   11,
    QMetaType::Void, 0x80000000 | 13,   14,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21, 0x80000000 | 21,   22,   23,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21,   26,

       0        // eod
};

void CourseWareWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CourseWareWidget *_t = static_cast<CourseWareWidget *>(_o);
        switch (_id) {
        case 0: _t->clearScreen((*reinterpret_cast< TS_UINT64(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->paintModeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->promptSent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->changeBackground((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 4: _t->changeMedia((*reinterpret_cast< QMediaPlayer*(*)>(_a[1]))); break;
        case 5: _t->on_tbStart_clicked(); break;
        case 6: _t->on_tbPrev_clicked(); break;
        case 7: _t->on_tbNext_clicked(); break;
        case 8: _t->on_tbUpload_clicked(); break;
        case 9: _t->on_tbSync_clicked(); break;
        case 10: _t->on_lsWare_currentItemChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2]))); break;
        case 11: _t->on_tbExitWare_clicked(); break;
        case 12: _t->on_lsWare_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
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
            typedef void (CourseWareWidget::*_t)(TS_UINT64 , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CourseWareWidget::clearScreen)) {
                *result = 0;
            }
        }
        {
            typedef void (CourseWareWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CourseWareWidget::paintModeChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (CourseWareWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CourseWareWidget::promptSent)) {
                *result = 2;
            }
        }
        {
            typedef void (CourseWareWidget::*_t)(QPixmap );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CourseWareWidget::changeBackground)) {
                *result = 3;
            }
        }
        {
            typedef void (CourseWareWidget::*_t)(QMediaPlayer * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CourseWareWidget::changeMedia)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject CourseWareWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CourseWareWidget.data,
      qt_meta_data_CourseWareWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *CourseWareWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CourseWareWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CourseWareWidget.stringdata))
        return static_cast<void*>(const_cast< CourseWareWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CourseWareWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void CourseWareWidget::clearScreen(TS_UINT64 _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CourseWareWidget::paintModeChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CourseWareWidget::promptSent(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CourseWareWidget::changeBackground(QPixmap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CourseWareWidget::changeMedia(QMediaPlayer * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtClassClient/LayerUI/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[27];
    char stringdata[323];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 14),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 7),
QT_MOC_LITERAL(4, 35, 9),
QT_MOC_LITERAL(5, 45, 8),
QT_MOC_LITERAL(6, 54, 4),
QT_MOC_LITERAL(7, 59, 4),
QT_MOC_LITERAL(8, 64, 11),
QT_MOC_LITERAL(9, 76, 9),
QT_MOC_LITERAL(10, 86, 3),
QT_MOC_LITERAL(11, 90, 10),
QT_MOC_LITERAL(12, 101, 8),
QT_MOC_LITERAL(13, 110, 8),
QT_MOC_LITERAL(14, 119, 16),
QT_MOC_LITERAL(15, 136, 6),
QT_MOC_LITERAL(16, 143, 10),
QT_MOC_LITERAL(17, 154, 16),
QT_MOC_LITERAL(18, 171, 9),
QT_MOC_LITERAL(19, 181, 9),
QT_MOC_LITERAL(20, 191, 21),
QT_MOC_LITERAL(21, 213, 5),
QT_MOC_LITERAL(22, 219, 20),
QT_MOC_LITERAL(23, 240, 22),
QT_MOC_LITERAL(24, 263, 25),
QT_MOC_LITERAL(25, 289, 20),
QT_MOC_LITERAL(26, 310, 12)
    },
    "MainWindow\0enOrLeaveClass\0\0entered\0"
    "drawShape\0addScene\0uidh\0uidl\0changeScene\0"
    "TS_UINT64\0uid\0enterClass\0username\0"
    "password\0enterClassResult\0result\0"
    "leaveClass\0leaveClassResult\0classIcon\0"
    "drawScene\0on_listWidget_clicked\0index\0"
    "on_tbMyClass_clicked\0on_btClassInfo_clicked\0"
    "on_tbTeacherBoard_clicked\0"
    "on_tbMyBoard_clicked\0addSceneSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    0,   97,    2, 0x06 /* Public */,
       5,    2,   98,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,  103,    2, 0x0a /* Public */,
      11,    2,  106,    2, 0x0a /* Public */,
      14,    1,  111,    2, 0x0a /* Public */,
      16,    0,  114,    2, 0x0a /* Public */,
      17,    1,  115,    2, 0x0a /* Public */,
      18,    1,  118,    2, 0x0a /* Public */,
      19,    0,  121,    2, 0x0a /* Public */,
      20,    1,  122,    2, 0x08 /* Private */,
      22,    0,  125,    2, 0x08 /* Private */,
      23,    0,  126,    2, 0x08 /* Private */,
      24,    0,  127,    2, 0x08 /* Private */,
      25,    0,  128,    2, 0x08 /* Private */,
      26,    2,  129,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   12,   13,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->enOrLeaveClass((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->drawShape(); break;
        case 2: _t->addScene((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->changeScene((*reinterpret_cast< TS_UINT64(*)>(_a[1]))); break;
        case 4: _t->enterClass((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->enterClassResult((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->leaveClass(); break;
        case 7: _t->leaveClassResult((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->classIcon((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->drawScene(); break;
        case 10: _t->on_listWidget_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 11: _t->on_tbMyClass_clicked(); break;
        case 12: _t->on_btClassInfo_clicked(); break;
        case 13: _t->on_tbTeacherBoard_clicked(); break;
        case 14: _t->on_tbMyBoard_clicked(); break;
        case 15: _t->addSceneSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::enOrLeaveClass)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::drawShape)) {
                *result = 1;
            }
        }
        {
            typedef void (MainWindow::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::addScene)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "CMsgObject"))
        return static_cast< CMsgObject*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::enOrLeaveClass(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::drawShape()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MainWindow::addScene(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE

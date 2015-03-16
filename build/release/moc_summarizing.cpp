/****************************************************************************
** Meta object code from reading C++ file 'summarizing.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../summarizing.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'summarizing.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_summarizing_t {
    QByteArrayData data[16];
    char stringdata[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_summarizing_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_summarizing_t qt_meta_stringdata_summarizing = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 11),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 3),
QT_MOC_LITERAL(4, 29, 5),
QT_MOC_LITERAL(5, 35, 5),
QT_MOC_LITERAL(6, 41, 3),
QT_MOC_LITERAL(7, 45, 8),
QT_MOC_LITERAL(8, 54, 4),
QT_MOC_LITERAL(9, 59, 9),
QT_MOC_LITERAL(10, 69, 13),
QT_MOC_LITERAL(11, 83, 1),
QT_MOC_LITERAL(12, 85, 7),
QT_MOC_LITERAL(13, 93, 4),
QT_MOC_LITERAL(14, 98, 11),
QT_MOC_LITERAL(15, 110, 8)
    },
    "summarizing\0write_excel\0\0row\0count\0"
    "Error\0str\0add_item\0type\0set_table\0"
    "QTableWidget*\0t\0add_row\0init\0clear_table\0"
    "to_excel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_summarizing[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   54,    2, 0x06 /* Public */,
       5,    1,   61,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,   64,    2, 0x0a /* Public */,
       9,    1,   69,    2, 0x0a /* Public */,
      12,    0,   72,    2, 0x0a /* Public */,
      13,    0,   73,    2, 0x0a /* Public */,
      14,    0,   74,    2, 0x0a /* Public */,
      15,    0,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,    3,    4,    2,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    8,    6,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void summarizing::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        summarizing *_t = static_cast<summarizing *>(_o);
        switch (_id) {
        case 0: _t->write_excel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->Error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->add_item((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->set_table((*reinterpret_cast< QTableWidget*(*)>(_a[1]))); break;
        case 4: _t->add_row(); break;
        case 5: _t->init(); break;
        case 6: _t->clear_table(); break;
        case 7: _t->to_excel(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTableWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (summarizing::*_t)(int , int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&summarizing::write_excel)) {
                *result = 0;
            }
        }
        {
            typedef void (summarizing::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&summarizing::Error)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject summarizing::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_summarizing.data,
      qt_meta_data_summarizing,  qt_static_metacall, 0, 0}
};


const QMetaObject *summarizing::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *summarizing::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_summarizing.stringdata))
        return static_cast<void*>(const_cast< summarizing*>(this));
    return QObject::qt_metacast(_clname);
}

int summarizing::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void summarizing::write_excel(int _t1, int _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void summarizing::Error(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

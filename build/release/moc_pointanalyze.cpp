/****************************************************************************
** Meta object code from reading C++ file 'pointanalyze.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../pointanalyze.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pointanalyze.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_pointAnalyze_t {
    QByteArrayData data[9];
    char stringdata[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_pointAnalyze_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_pointAnalyze_t qt_meta_stringdata_pointAnalyze = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 10),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 13),
QT_MOC_LITERAL(4, 39, 8),
QT_MOC_LITERAL(5, 48, 7),
QT_MOC_LITERAL(6, 56, 1),
QT_MOC_LITERAL(7, 58, 1),
QT_MOC_LITERAL(8, 60, 6)
    },
    "pointAnalyze\0initDevice\0\0timer_timeout\0"
    "showData\0double*\0x\0y\0length"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_pointAnalyze[] = {

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
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   30,    2, 0x08 /* Private */,
       4,    3,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5, QMetaType::Int,    6,    7,    8,

       0        // eod
};

void pointAnalyze::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        pointAnalyze *_t = static_cast<pointAnalyze *>(_o);
        switch (_id) {
        case 0: _t->initDevice(); break;
        case 1: _t->timer_timeout(); break;
        case 2: _t->showData((*reinterpret_cast< double*(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (pointAnalyze::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&pointAnalyze::initDevice)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject pointAnalyze::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_pointAnalyze.data,
      qt_meta_data_pointAnalyze,  qt_static_metacall, 0, 0}
};


const QMetaObject *pointAnalyze::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *pointAnalyze::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_pointAnalyze.stringdata))
        return static_cast<void*>(const_cast< pointAnalyze*>(this));
    return QDialog::qt_metacast(_clname);
}

int pointAnalyze::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void pointAnalyze::initDevice()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

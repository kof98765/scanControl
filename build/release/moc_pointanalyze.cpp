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
    QByteArrayData data[11];
    char stringdata[171];
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
QT_MOC_LITERAL(3, 25, 21),
QT_MOC_LITERAL(4, 47, 20),
QT_MOC_LITERAL(5, 68, 19),
QT_MOC_LITERAL(6, 88, 16),
QT_MOC_LITERAL(7, 105, 24),
QT_MOC_LITERAL(8, 130, 4),
QT_MOC_LITERAL(9, 135, 21),
QT_MOC_LITERAL(10, 157, 13)
    },
    "pointAnalyze\0initDevice\0\0on_loadButton_clicked\0"
    "on_nextFrame_clicked\0on_preFrame_clicked\0"
    "on_reset_clicked\0on_numFrame_valueChanged\0"
    "arg1\0on_pushButton_clicked\0timer_timeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_pointAnalyze[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    1,   59,    2, 0x08 /* Private */,
       9,    0,   62,    2, 0x08 /* Private */,
      10,    0,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void pointAnalyze::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        pointAnalyze *_t = static_cast<pointAnalyze *>(_o);
        switch (_id) {
        case 0: _t->initDevice(); break;
        case 1: _t->on_loadButton_clicked(); break;
        case 2: _t->on_nextFrame_clicked(); break;
        case 3: _t->on_preFrame_clicked(); break;
        case 4: _t->on_reset_clicked(); break;
        case 5: _t->on_numFrame_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_pushButton_clicked(); break;
        case 7: _t->timer_timeout(); break;
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
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void pointAnalyze::initDevice()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
/****************************************************************************
** Meta object code from reading C++ file 'dialognetparam.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../dialognetparam.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialognetparam.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DialogNetParam_t {
    QByteArrayData data[14];
    char stringdata[201];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogNetParam_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogNetParam_t qt_meta_stringdata_DialogNetParam = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 7),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 3),
QT_MOC_LITERAL(4, 28, 8),
QT_MOC_LITERAL(5, 37, 5),
QT_MOC_LITERAL(6, 43, 21),
QT_MOC_LITERAL(7, 65, 15),
QT_MOC_LITERAL(8, 81, 20),
QT_MOC_LITERAL(9, 102, 21),
QT_MOC_LITERAL(10, 124, 36),
QT_MOC_LITERAL(11, 161, 5),
QT_MOC_LITERAL(12, 167, 28),
QT_MOC_LITERAL(13, 196, 4)
    },
    "DialogNetParam\0netTest\0\0msg\0recvData\0"
    "char*\0on_Button_Yes_clicked\0on_open_clicked\0"
    "on_default_2_clicked\0on_sendButton_clicked\0"
    "on_resampleValue_currentIndexChanged\0"
    "index\0on_profileCount_valueChanged\0"
    "arg1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogNetParam[] = {

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
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   57,    2, 0x0a /* Public */,
       6,    0,   60,    2, 0x08 /* Private */,
       7,    0,   61,    2, 0x08 /* Private */,
       8,    0,   62,    2, 0x08 /* Private */,
       9,    0,   63,    2, 0x08 /* Private */,
      10,    1,   64,    2, 0x08 /* Private */,
      12,    1,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   13,

       0        // eod
};

void DialogNetParam::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogNetParam *_t = static_cast<DialogNetParam *>(_o);
        switch (_id) {
        case 0: _t->netTest((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->recvData((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 2: _t->on_Button_Yes_clicked(); break;
        case 3: _t->on_open_clicked(); break;
        case 4: _t->on_default_2_clicked(); break;
        case 5: _t->on_sendButton_clicked(); break;
        case 6: _t->on_resampleValue_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_profileCount_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DialogNetParam::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DialogNetParam::netTest)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject DialogNetParam::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogNetParam.data,
      qt_meta_data_DialogNetParam,  qt_static_metacall, 0, 0}
};


const QMetaObject *DialogNetParam::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogNetParam::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogNetParam.stringdata))
        return static_cast<void*>(const_cast< DialogNetParam*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogNetParam::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void DialogNetParam::netTest(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

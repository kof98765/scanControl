/****************************************************************************
** Meta object code from reading C++ file 'reflectcontrol.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../reflectcontrol.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'reflectcontrol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_reflectControl_t {
    QByteArrayData data[19];
    char stringdata[206];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_reflectControl_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_reflectControl_t qt_meta_stringdata_reflectControl = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 9),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 11),
QT_MOC_LITERAL(4, 38, 8),
QT_MOC_LITERAL(5, 47, 5),
QT_MOC_LITERAL(6, 53, 5),
QT_MOC_LITERAL(7, 59, 7),
QT_MOC_LITERAL(8, 67, 7),
QT_MOC_LITERAL(9, 75, 10),
QT_MOC_LITERAL(10, 86, 13),
QT_MOC_LITERAL(11, 100, 8),
QT_MOC_LITERAL(12, 109, 14),
QT_MOC_LITERAL(13, 124, 8),
QT_MOC_LITERAL(14, 133, 13),
QT_MOC_LITERAL(15, 147, 4),
QT_MOC_LITERAL(16, 152, 12),
QT_MOC_LITERAL(17, 165, 28),
QT_MOC_LITERAL(18, 194, 11)
    },
    "reflectControl\0makeAMove\0\0startDetect\0"
    "recvData\0char*\0Error\0netTest\0udpDate\0"
    "takeAPhoto\0setConfigFile\0fileName\0"
    "setImgFilePath\0filePath\0setServerPort\0"
    "Port\0displayError\0QAbstractSocket::SocketError\0"
    "socketError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_reflectControl[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    1,   71,    2, 0x06 /* Public */,
       6,    1,   74,    2, 0x06 /* Public */,
       7,    1,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   80,    2, 0x0a /* Public */,
       9,    0,   81,    2, 0x0a /* Public */,
      10,    1,   82,    2, 0x0a /* Public */,
      12,    1,   85,    2, 0x0a /* Public */,
      14,    1,   88,    2, 0x0a /* Public */,
      16,    1,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, 0x80000000 | 17,   18,

       0        // eod
};

void reflectControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        reflectControl *_t = static_cast<reflectControl *>(_o);
        switch (_id) {
        case 0: _t->makeAMove(); break;
        case 1: _t->startDetect(); break;
        case 2: _t->recvData((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 3: _t->Error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->netTest((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->udpDate(); break;
        case 6: _t->takeAPhoto(); break;
        case 7: _t->setConfigFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->setImgFilePath((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->setServerPort((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (reflectControl::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&reflectControl::makeAMove)) {
                *result = 0;
            }
        }
        {
            typedef void (reflectControl::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&reflectControl::startDetect)) {
                *result = 1;
            }
        }
        {
            typedef void (reflectControl::*_t)(char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&reflectControl::recvData)) {
                *result = 2;
            }
        }
        {
            typedef void (reflectControl::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&reflectControl::Error)) {
                *result = 3;
            }
        }
        {
            typedef void (reflectControl::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&reflectControl::netTest)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject reflectControl::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_reflectControl.data,
      qt_meta_data_reflectControl,  qt_static_metacall, 0, 0}
};


const QMetaObject *reflectControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *reflectControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_reflectControl.stringdata))
        return static_cast<void*>(const_cast< reflectControl*>(this));
    return QThread::qt_metacast(_clname);
}

int reflectControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void reflectControl::makeAMove()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void reflectControl::startDetect()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void reflectControl::recvData(char * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void reflectControl::Error(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void reflectControl::netTest(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE

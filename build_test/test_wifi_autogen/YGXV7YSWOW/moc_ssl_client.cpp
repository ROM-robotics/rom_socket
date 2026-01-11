/****************************************************************************
** Meta object code from reading C++ file 'ssl_client.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/ssl_client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ssl_client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SslClient_t {
    const uint offsetsAndSize[48];
    char stringdata0[291];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_SslClient_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_SslClient_t qt_meta_stringdata_SslClient = {
    {
QT_MOC_LITERAL(0, 9), // "SslClient"
QT_MOC_LITERAL(10, 9), // "connected"
QT_MOC_LITERAL(20, 0), // ""
QT_MOC_LITERAL(21, 12), // "disconnected"
QT_MOC_LITERAL(34, 15), // "connectionError"
QT_MOC_LITERAL(50, 5), // "error"
QT_MOC_LITERAL(56, 8), // "sslError"
QT_MOC_LITERAL(65, 16), // "responseReceived"
QT_MOC_LITERAL(82, 8), // "response"
QT_MOC_LITERAL(91, 14), // "uploadProgress"
QT_MOC_LITERAL(106, 9), // "bytesSent"
QT_MOC_LITERAL(116, 10), // "bytesTotal"
QT_MOC_LITERAL(127, 14), // "uploadFinished"
QT_MOC_LITERAL(142, 7), // "success"
QT_MOC_LITERAL(150, 8), // "filename"
QT_MOC_LITERAL(159, 11), // "onConnected"
QT_MOC_LITERAL(171, 14), // "onDisconnected"
QT_MOC_LITERAL(186, 11), // "onReadyRead"
QT_MOC_LITERAL(198, 11), // "onSslErrors"
QT_MOC_LITERAL(210, 16), // "QList<QSslError>"
QT_MOC_LITERAL(227, 6), // "errors"
QT_MOC_LITERAL(234, 15), // "onErrorOccurred"
QT_MOC_LITERAL(250, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(279, 11) // "socketError"

    },
    "SslClient\0connected\0\0disconnected\0"
    "connectionError\0error\0sslError\0"
    "responseReceived\0response\0uploadProgress\0"
    "bytesSent\0bytesTotal\0uploadFinished\0"
    "success\0filename\0onConnected\0"
    "onDisconnected\0onReadyRead\0onSslErrors\0"
    "QList<QSslError>\0errors\0onErrorOccurred\0"
    "QAbstractSocket::SocketError\0socketError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SslClient[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x06,    1 /* Public */,
       3,    0,   87,    2, 0x06,    2 /* Public */,
       4,    1,   88,    2, 0x06,    3 /* Public */,
       6,    1,   91,    2, 0x06,    5 /* Public */,
       7,    1,   94,    2, 0x06,    7 /* Public */,
       9,    2,   97,    2, 0x06,    9 /* Public */,
      12,    2,  102,    2, 0x06,   12 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      15,    0,  107,    2, 0x08,   15 /* Private */,
      16,    0,  108,    2, 0x08,   16 /* Private */,
      17,    0,  109,    2, 0x08,   17 /* Private */,
      18,    1,  110,    2, 0x08,   18 /* Private */,
      21,    1,  113,    2, 0x08,   20 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   10,   11,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,   13,   14,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, 0x80000000 | 22,   23,

       0        // eod
};

void SslClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SslClient *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->connectionError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->sslError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->responseReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->uploadProgress((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qint64>>(_a[2]))); break;
        case 6: _t->uploadFinished((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 7: _t->onConnected(); break;
        case 8: _t->onDisconnected(); break;
        case 9: _t->onReadyRead(); break;
        case 10: _t->onSslErrors((*reinterpret_cast< std::add_pointer_t<QList<QSslError>>>(_a[1]))); break;
        case 11: _t->onErrorOccurred((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QSslError> >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SslClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SslClient::connected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SslClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SslClient::disconnected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SslClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SslClient::connectionError)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SslClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SslClient::sslError)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SslClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SslClient::responseReceived)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SslClient::*)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SslClient::uploadProgress)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SslClient::*)(bool , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SslClient::uploadFinished)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject SslClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SslClient.offsetsAndSize,
    qt_meta_data_SslClient,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_SslClient_t
, QtPrivate::TypeAndForceComplete<SslClient, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qint64, std::false_type>, QtPrivate::TypeAndForceComplete<qint64, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QList<QSslError> &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>


>,
    nullptr
} };


const QMetaObject *SslClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SslClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SslClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SslClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void SslClient::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SslClient::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SslClient::connectionError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SslClient::sslError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SslClient::responseReceived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SslClient::uploadProgress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SslClient::uploadFinished(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

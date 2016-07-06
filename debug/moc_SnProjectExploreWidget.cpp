/****************************************************************************
** Meta object code from reading C++ file 'SnProjectExploreWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/widget/SnProjectExploreWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SnProjectExploreWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SnProjectExploreWidget_t {
    QByteArrayData data[16];
    char stringdata0[215];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SnProjectExploreWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SnProjectExploreWidget_t qt_meta_stringdata_SnProjectExploreWidget = {
    {
QT_MOC_LITERAL(0, 0, 22), // "SnProjectExploreWidget"
QT_MOC_LITERAL(1, 23, 10), // "mousePress"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "index"
QT_MOC_LITERAL(4, 41, 25), // "slotSpriteAttributeChange"
QT_MOC_LITERAL(5, 67, 9), // "SnSprite*"
QT_MOC_LITERAL(6, 77, 6), // "sprite"
QT_MOC_LITERAL(7, 84, 13), // "slotSpriteAdd"
QT_MOC_LITERAL(8, 98, 10), // "SnProject*"
QT_MOC_LITERAL(9, 109, 4), // "proj"
QT_MOC_LITERAL(10, 114, 16), // "slotSpriteRemove"
QT_MOC_LITERAL(11, 131, 28), // "slotAnimationAttributeChange"
QT_MOC_LITERAL(12, 160, 12), // "SnAnimation*"
QT_MOC_LITERAL(13, 173, 4), // "anim"
QT_MOC_LITERAL(14, 178, 16), // "slotAnimationAdd"
QT_MOC_LITERAL(15, 195, 19) // "slotAnimationRemove"

    },
    "SnProjectExploreWidget\0mousePress\0\0"
    "index\0slotSpriteAttributeChange\0"
    "SnSprite*\0sprite\0slotSpriteAdd\0"
    "SnProject*\0proj\0slotSpriteRemove\0"
    "slotAnimationAttributeChange\0SnAnimation*\0"
    "anim\0slotAnimationAdd\0slotAnimationRemove"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SnProjectExploreWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x0a /* Public */,
       4,    1,   52,    2, 0x0a /* Public */,
       7,    2,   55,    2, 0x0a /* Public */,
      10,    2,   60,    2, 0x0a /* Public */,
      11,    1,   65,    2, 0x0a /* Public */,
      14,    2,   68,    2, 0x0a /* Public */,
      15,    2,   73,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 5,    9,    6,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 5,    9,    6,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 12,    6,   13,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 12,    6,   13,

       0        // eod
};

void SnProjectExploreWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SnProjectExploreWidget *_t = static_cast<SnProjectExploreWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mousePress((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->slotSpriteAttributeChange((*reinterpret_cast< SnSprite*(*)>(_a[1]))); break;
        case 2: _t->slotSpriteAdd((*reinterpret_cast< SnProject*(*)>(_a[1])),(*reinterpret_cast< SnSprite*(*)>(_a[2]))); break;
        case 3: _t->slotSpriteRemove((*reinterpret_cast< SnProject*(*)>(_a[1])),(*reinterpret_cast< SnSprite*(*)>(_a[2]))); break;
        case 4: _t->slotAnimationAttributeChange((*reinterpret_cast< SnAnimation*(*)>(_a[1]))); break;
        case 5: _t->slotAnimationAdd((*reinterpret_cast< SnSprite*(*)>(_a[1])),(*reinterpret_cast< SnAnimation*(*)>(_a[2]))); break;
        case 6: _t->slotAnimationRemove((*reinterpret_cast< SnSprite*(*)>(_a[1])),(*reinterpret_cast< SnAnimation*(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject SnProjectExploreWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SnProjectExploreWidget.data,
      qt_meta_data_SnProjectExploreWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SnProjectExploreWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SnProjectExploreWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SnProjectExploreWidget.stringdata0))
        return static_cast<void*>(const_cast< SnProjectExploreWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int SnProjectExploreWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

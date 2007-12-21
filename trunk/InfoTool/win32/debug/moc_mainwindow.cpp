/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Fri 21. Dec 10:45:45 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_MainWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      24,   11,   11,   11, 0x08,
      31,   11,   11,   11, 0x08,
      38,   11,   11,   11, 0x08,
      47,   11,   11,   11, 0x08,
      70,   64,   11,   11, 0x08,
      85,   81,   11,   11, 0x08,
      94,   64,   11,   11, 0x08,
     104,   11,   11,   11, 0x08,
     112,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0newWindow()\0open()\0save()\0"
    "saveAs()\0openRecentFile()\0index\0"
    "title(int)\0num\0vts(int)\0view(int)\0"
    "about()\0update()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

const QMetaObject *MainWindow::metaObject() const
{
    return &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
	return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newWindow(); break;
        case 1: open(); break;
        case 2: save(); break;
        case 3: saveAs(); break;
        case 4: openRecentFile(); break;
        case 5: title((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: vts((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: view((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: about(); break;
        case 9: update(); break;
        }
        _id -= 10;
    }
    return _id;
}

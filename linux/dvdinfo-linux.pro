#########################################################
#  DVD Info project for Linux (Ubuntu-Gutsy)
#
#  version: 0.1.4
#  license: GNU GPL
#  author & copyright: starbuck<starbuck@labdv.com>
#  date: 12-Dec-2007
#########################################################

# restrict to unix (but not macx) spec
CONFIG(!unix|macx) {
  error(Qmake project file only for Linux (Ubuntu-Gutsy) platform)
}

# Linux platforms
#################
message(Running Qmake for Linux platform)
TEMPLATE = app
TARGET = dvdinfo
LANGUAGE = C++
CONFIG += debug release
CONFIG += qt
HEADERS += ../src/dvdtitleinfoview.h \
    ../src/dvdinfoview.h \
    ../src/dvdinfocore.h \
    ../src/mainwindow.h
SOURCES += ../src/dvdtitleinfoview.cpp \
    ../src/dvdinfoview.cpp \
    ../src/dvdinfocore.cpp \
    ../src/mainwindow.cpp \
    ../src/main.cpp
LIBS += -ldvdread \
    -ldvdcss
DEFINES += __STDC_LIMIT_MACROS

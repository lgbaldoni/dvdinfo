#########################################################
#  DVD Info project for Mac OS X (Leopard-Xcode)
#
#  version: 0.1.4
#  license: GNU GPL
#  author & copyright: starbuck<starbuck@labdv.com>
#  date: 12-Dec-2007
#########################################################

# restrict to macx spec
!macx:error(Qmake project file only for MacX (Leopard-Xcode) platform)

# Mac OS X platform
###################
# run Qmake to create the Xcode project file
message(Running Qmake for Mac OS X (Xcode) platform)
TEMPLATE = app
TARGET = DVDinfo
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

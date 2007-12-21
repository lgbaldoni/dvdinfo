# #######################################################
# DVD Info project for Win32 (Eclipse-MinGW)
# version: 0.1.4
# license: GNU GPL
# author & copyright: starbuck<starbuck@labdv.com>
# date: 12-Dec-2007
# #######################################################
# restrict to win32 spec (helpful in Qmake command mode)
!win32:error(Qmake project file only for Win32 (Eclipse-MinGW) platform)

# Win32 GNU (MinGW)
# ##################
message(Running Qmake for Win32 (Eclipse-MinGW) platform)
TEMPLATE = app
LANGUAGE = C++
CONFIG += debug \
    release
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
TARGET = dvdinfo
LIBS += -ldvdread \
    -ldvdcss
DEFINES += __STDC_LIMIT_MACROS

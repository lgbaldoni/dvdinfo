#############################################################################
# Makefile for building: DVDinfo.app/Contents/MacOS/DVDinfo
# Generated by qmake (2.01a) (Qt 4.3.2) on: dim. janv. 6 16:33:57 2008
# Project:  dvdinfo-macx.pro
# Template: app
# Command: /usr/bin/qmake -macx -o DVDinfo.xcodeproj/project.pbxproj dvdinfo-macx.pro
#############################################################################

MOC       = /Developer/Tools/Qt/moc
UIC       = /Developer/Tools/Qt/uic
LEX       = flex
LEXFLAGS  = 
YACC      = yacc
YACCFLAGS = -d
DEFINES       = -D__STDC_LIMIT_MACROS -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
INCPATH       = -I/usr/local/Qt4.3/mkspecs/macx-xcode -I. -I/Library/Frameworks/QtCore.framework/Versions/4/Headers -I/usr/include/QtCore -I/Library/Frameworks/QtGui.framework/Versions/4/Headers -I/usr/include/QtGui -I/usr/include -I. -I. -I/usr/local/include -I/System/Library/Frameworks/CarbonCore.framework/Headers
DEL_FILE  = rm -f
MOVE      = mv -f

IMAGES = 
PARSERS =
preprocess: $(PARSERS) compilers
clean preprocess_clean: parser_clean compiler_clean

parser_clean:
mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compilers: ./moc_dvdtitleinfoview.cpp ./moc_dvdinfoview.cpp ./moc_mainwindow.cpp
compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_moc_header_make_all: moc_dvdtitleinfoview.cpp moc_dvdinfoview.cpp moc_mainwindow.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_dvdtitleinfoview.cpp moc_dvdinfoview.cpp moc_mainwindow.cpp
moc_dvdtitleinfoview.cpp: ../src/dvdinfocore.h \
		../src/dvdtitleinfoview.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ ../src/dvdtitleinfoview.h -o moc_dvdtitleinfoview.cpp

moc_dvdinfoview.cpp: ../src/dvdinfoview.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ ../src/dvdinfoview.h -o moc_dvdinfoview.cpp

moc_mainwindow.cpp: ../src/dvdinfocore.h \
		../src/mainwindow.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ ../src/mainwindow.h -o moc_mainwindow.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 


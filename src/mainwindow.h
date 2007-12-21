/*****************************************************************************
 *
 *  mainwindow.h -- MainWindow class extends QMainWindow
 * 
 *  Copyright (C) 2007 Starbuck <starbuck@labdv.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *
 *****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "dvdinfocore.h"

class QAction;
class QSignalMapper;
class QMenu;
class QTextEdit;
class QActionGroup;
class QStackedWidget;

class DvdInfoView;
class DvdTitleInfoView;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

private slots:
	void newWindow();
	void open();
	void save();
	void saveAs();
	void openRecentFile();
	void title(int index);
	void vts(int num);
	void view(int index);
	void about();
	void update();

private:
	void createActions();
	void createTitleActions();
	void createVtsActions();
	void createMenus();
	void loadDvdInfo(const QString &dvdPath);
	void saveDvdInfo(const QString &infoFilePath);
	void loadDvdTitleInfo(const QString &dvdPath, int title);
	void saveDvdTitleInfo(const QString &infoFilePath, int title);
	void setCurrentDvdPath(const QString &dvdPath);
	void updateRecentFileActions();
	QString getDvdInfoTextView(const QString &all );
	QString getDvdTitleInfoTextView(const QString &all );
	
	QSignalMapper *titlesSignalMapper;
	QSignalMapper *vtsSignalMapper;
	QSignalMapper *viewSignalMapper;
	
	QString strippedName(const QString &fullFileName);
	QString curFile;

	QStackedWidget *views;
	DvdInfoView *stdView;
	DvdTitleInfoView *stdTitleView;
	QTextEdit *txtView;
	QTextEdit *allView;
	QMenu *fileMenu;
	QMenu *titlesMenu;
	QMenu *vtsMenu;
	QMenu *viewMenu;
	QMenu *helpMenu;
	QAction *newAct;
	QAction *openAct;
	QAction *saveAct;
	QAction *exitAct;
	QAction *vtsAct[99];
	QAction *titleAct[99];
	QActionGroup *viewGroup;
	QAction *viewStdAct;
	QAction *viewTxtAct;
	QAction *viewAllAct;
	QAction *updateAct;
	QAction *aboutAct;
	QAction *aboutQtAct;
	QAction *separatorAct;

	enum { MaxRecentFiles = 5 };
	QAction *recentFileActs[MaxRecentFiles];
	
	dvdInfo_t currentDvdInfo;
	dvdTitleInfo_t currentDvdTitleInfo;};

#endif

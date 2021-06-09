/*****************************************************************************
 *
 *  mainwindow.cpp -- MainWindow class extends QMainWindow
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

#include <QtGui>
#include <QRegExp>
#include <stdint.h>
#include <iostream>  // for console developer messages like: cout << "Set view: " << index << endl;

#include "dvdinfoview.h"
#include "dvdtitleinfoview.h"
#include "mainwindow.h"
	
using namespace DvdInfoCore;

MainWindow::MainWindow()
{
	setAttribute(Qt::WA_DeleteOnClose);

#ifdef QT_NO_DEBUG
	appName = tr("DVDx InfoTool");	
#else
	appName = tr("DVDx InfoTool (Debug)");		
#endif
	
	QFont infoFont("Courier");
	infoFont.setStyleHint(QFont::TypeWriter);
	
	stdView = new DvdInfoView;
	stdTitleView = new DvdTitleInfoView;
		
	txtView = new QTextEdit;
	txtView->setReadOnly(true);
	txtView->setFont(infoFont);
	txtView->setLineWrapMode(QTextEdit::NoWrap);
	
	allView = new QTextEdit;
	allView->setReadOnly(true);
	allView->setFont(infoFont);
	allView->setLineWrapMode(QTextEdit::NoWrap);

	views = new QStackedWidget;
	views->addWidget(stdView);
	views->addWidget(txtView);
	views->addWidget(allView);
	views->setCurrentWidget(txtView);
	setCentralWidget(views);	
	
	createActions();
	createMenus();
	(void)statusBar();

	setWindowTitle(appName);	
	
#ifdef WIN32
	resize(640, 720);
#else
	resize(720, 720);
#endif
}

void MainWindow::newWindow()
{
	MainWindow *other = new MainWindow;
	other->show();
}

void MainWindow::open()
{
	QString dvdPath = QFileDialog::getExistingDirectory(this,
			tr("Open DVD VIDEO_TS Folder"),
			"/",
			QFileDialog::ShowDirsOnly); ;
	if (!dvdPath.isEmpty())
		loadDvdInfo(dvdPath);
}

void MainWindow::reload()
{
	if (!curFile.isEmpty())
		loadDvdInfo(curFile);
}

void MainWindow::save()
{
	if (curFile.isEmpty())
		saveAs();
	else
		saveDvdInfo(curFile);
}

void MainWindow::saveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this);
	if (fileName.isEmpty())
		return;

	saveDvdInfo(fileName);
}

void MainWindow::openRecentFile()
{
	QAction *action = qobject_cast<QAction *>(sender());
	if (action)
		loadDvdInfo(action->data().toString());
}

void MainWindow::title(int index)
{
	// note: title number is title index + 1	
	loadDvdTitleInfo( curFile, index + 1 );
}

void MainWindow::vts(int index)
{
	// note: vts number is vts index + 1
	loadDvdVtsInfo( curFile, index + 1 );
}

void MainWindow::view(int index)
{	
	switch (index) {
		case 1: 
			views->setCurrentIndex(0);
			statusBar()->showMessage(tr("Display toggled to standard view"), 2000);
			break;
		case 2: 
			views->setCurrentIndex(1);
			statusBar()->showMessage(tr("Display toggled to default text view"), 2000);
			break;
		case 3: 
			views->setCurrentIndex(2);
			statusBar()->showMessage(tr("Display toggled to view all"), 2000);
			break;
	}
}

void MainWindow::about()
{
   QMessageBox::about(this, tr("About DVDx InfoTool"),
			tr("<br><b>About DVDx InfoTool</b><br><br>"
			"Version 0.9.2 (Pre-release)<br>"
			"Author: <a href='mailto:starbuck@labdv.com?subject=DVDx "
			" InfoTool'>Starbuck&lt;starbuck@labdv.com&gt;</a><br><br>"
			"The <b>DVDx InfoTool</b> utility shows many properties "
   			"of a DVD-Video content, these informations may be "
   			"very helpful to set DVD playing or DVD encoding "
   			"parameters. It is a perfect companion for "
   			"<a href='http://www.labdv.com/dvdx'>DVDx encoder</a>."));
}

void MainWindow::update()
{
   QMessageBox::about(this, tr("DVDx InfoTool new updates"),
			tr("Click the <b><a href='http://www.labdv.com/dvdx/"
			"infotool/version.php?v=0.9.2'>check for DVDx InfoTool "
			"updates link</a></b> to connect to the application homepage."));
}

void MainWindow::createActions()
{
	newAct = new QAction(tr("&New window..."), this);
	newAct->setShortcut(tr("Ctrl+N"));
	newAct->setStatusTip(tr("Open new DVDx InfoTool window from current"));
	connect(newAct, SIGNAL(triggered()), this, SLOT(newWindow()));
	
	openAct = new QAction(tr("&Open DVD..."), this);
	openAct->setShortcut(tr("Ctrl+O"));
	openAct->setStatusTip(tr("Open DVD or VIDEO_TS folder or IFO file"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	saveAct = new QAction(tr("&Save informations..."), this);
	saveAct->setShortcut(tr("Ctrl+S"));
	saveAct->setStatusTip(tr("Save DVD informations to text file"));
	connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));
	saveAct->setDisabled(true);

	for (int i = 0; i < MaxRecentFiles; ++i) {
		recentFileActs[i] = new QAction(this);
		recentFileActs[i]->setVisible(false);
		connect(recentFileActs[i], SIGNAL(triggered()),
				this, SLOT(openRecentFile()));
	}

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcut(tr("Ctrl+Q"));
	exitAct->setStatusTip(tr("Exit the application"));
	connect(exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

	reloadAct = new QAction(tr("&DVD informations"), this);
	reloadAct->setStatusTip(tr("Reload current DVD informations"));
	connect(reloadAct, SIGNAL(triggered()), this, SLOT(reload()));
	
	for (int i = 0; i < 99; i++) {
		vtsAct[i] = 0;
	}
	
	for (int i = 0; i < 99; i++) {
		titleAct[i] = 0;
	}
	
	viewSignalMapper = new QSignalMapper(this);

	viewStdAct = new QAction(tr("&Standard"), this);
	viewStdAct->setStatusTip(tr("View commonly used DVD-Video informations"));
	viewStdAct->setCheckable(true);
	//viewStdAct->setChecked(true);
	viewStdAct->setDisabled(true);
	connect(viewStdAct, SIGNAL(triggered()), viewSignalMapper, SLOT(map()));

	viewTxtAct = new QAction(tr("&Text"), this);
	viewTxtAct->setStatusTip(tr("View most DVD-Video informations in plain text"));
	viewTxtAct->setCheckable(true);
	viewTxtAct->setChecked(true);
	connect(viewTxtAct, SIGNAL(triggered()), viewSignalMapper, SLOT(map()));
	
	viewAllAct = new QAction(tr("&All"), this);
	viewAllAct->setStatusTip(tr("Show all DVD informations available in plain text"));
	viewAllAct->setCheckable(true);
	connect(viewAllAct, SIGNAL(triggered()), viewSignalMapper, SLOT(map()));
	
	viewSignalMapper->setMapping(viewStdAct, 1);
	viewSignalMapper->setMapping(viewTxtAct, 2);	
	viewSignalMapper->setMapping(viewAllAct, 3);
	connect(viewSignalMapper, SIGNAL(mapped(int)), this, SLOT(view(int)));
	
	viewGroup = new QActionGroup(this);
	viewGroup->addAction(viewStdAct);
	viewGroup->addAction(viewTxtAct);
	viewGroup->addAction(viewAllAct);
	viewGroup->setExclusive(true);
	
	updateAct = new QAction(tr("&Check for new updates..."), this);
	updateAct->setStatusTip(tr("Connect to DVDx Infotool homepage"));
	connect(updateAct, SIGNAL(triggered()), this, SLOT(update()));
	
	aboutAct = new QAction(tr("&About DVDx IntoTool"), this);
	aboutAct->setStatusTip(tr("Show the DVDx InfoTool's About box"));
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

	aboutQtAct = new QAction(tr("About &Qt"), this);
	aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
	connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createTitleActions()
{
	for (int i = 0; i < 99; i++) {
		if ( titleAct[i] ) {
			delete titleAct[i];
			titleAct[i] = 0;
		}
	}

	if ( !currentDvdInfo.valid )
		return;
	
	if ( currentDvdInfo.titles < 1 )
		return;
	
	titlesMenu->addSeparator();
	
	titlesSignalMapper = new QSignalMapper(this);

	for (int i = 0; i < currentDvdInfo.titles; ++i) {
		titleAct[i] = new QAction(tr("Title %1 informations...").arg(i+1), this);
		titleAct[i]->setStatusTip(tr("Show DVD title informations"));
		connect(titleAct[i], SIGNAL(triggered()), titlesSignalMapper, SLOT(map()));	
		titlesSignalMapper->setMapping(titleAct[i], i);
		titlesMenu->addAction(titleAct[i]);
	}
	connect(titlesSignalMapper, SIGNAL(mapped(int)), this, SLOT(title(int)));

	titlesMenu->setEnabled(true);
}

void MainWindow::createVtsActions()
{
	for (int i = 0; i < 99; i++) {
		if ( vtsAct[i] ) {
			delete vtsAct[i];
			vtsAct[i] = 0;
		}
	}

	if ( !currentDvdInfo.valid )
		return;
	
	if ( currentDvdInfo.vtsnum < 1 )
		return;
	
	vtsMenu->addSeparator();
	
	vtsSignalMapper = new QSignalMapper(this);

	for (int i = 0; i < currentDvdInfo.vtsnum; ++i) {
		vtsAct[i] = new QAction(tr("VTS %1 informations...").arg(i+1), this);
		vtsAct[i]->setStatusTip(tr("Show Video Title Set informations"));
		connect(vtsAct[i], SIGNAL(triggered()), vtsSignalMapper, SLOT(map()));	
		vtsSignalMapper->setMapping(vtsAct[i], i);
		vtsMenu->addAction(vtsAct[i]);
	}
	connect(vtsSignalMapper, SIGNAL(mapped(int)), this, SLOT(vts(int)));

	vtsMenu->setEnabled(true);
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAct);
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	separatorAct = fileMenu->addSeparator();
	for (int i = 0; i < MaxRecentFiles; ++i)
		fileMenu->addAction(recentFileActs[i]);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);
	updateRecentFileActions();

	menuBar()->addSeparator();
	
	vtsMenu = menuBar()->addMenu(tr("&VTS"));
	vtsMenu->addAction(reloadAct);
	vtsMenu->setEnabled(false);
	
	menuBar()->addSeparator();
	
	titlesMenu = menuBar()->addMenu(tr("&Titles"));
	titlesMenu->addAction(reloadAct);
	titlesMenu->setEnabled(false);
	
	menuBar()->addSeparator();
	
	viewMenu = menuBar()->addMenu(tr("&View"));
	viewMenu->addAction(viewStdAct);
	viewMenu->addAction(viewTxtAct);
	viewMenu->addAction(viewAllAct);
	
	menuBar()->addSeparator();
	
	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(updateAct);
	helpMenu->addAction(aboutAct);
	//helpMenu->addAction(aboutQtAct);
}

void MainWindow::loadDvdInfo(const QString &dvdPath)
{
	currentDvdInfo = ReadDvdInfo( (const char *) dvdPath.toAscii() );

	if ( !currentDvdInfo.valid ) {
		QMessageBox::warning(this, tr("DVDx InfoTool"),
							 tr("Cannot load DVD informations:\n\n%1\n")
							 .arg(currentDvdInfo.errmsg));
		return;
	}

	stdView->setPath( currentDvdInfo.path );
	stdView->setVtsN( currentDvdInfo.vtsnum );
	stdView->resetInfo();
	for ( int i = 0; i < currentDvdInfo.vtsnum; i++) {
		stdView->addInfo( i + 1 , "VTS data isn't available in this version");
	}
	
	QString str = currentDvdInfo.text;
	QApplication::setOverrideCursor(Qt::WaitCursor);
	allView->setPlainText( str );
	QApplication::restoreOverrideCursor();
	
	QString strView = getDvdInfoTextView( str );
	
	QApplication::setOverrideCursor(Qt::WaitCursor);
	txtView->setPlainText( strView );
	QApplication::restoreOverrideCursor();	

/*
	int currentView = views->currentIndex();
	if ( views->widget(0) != (QWidget *) stdView ) {
		views->removeWidget(stdTitleView);
		views->insertWidget( 0 , stdView );
	}
	views->setCurrentIndex( currentView );
standard view is not available in this version */
	
	setCurrentDvdPath(dvdPath);
	createVtsActions();
	createTitleActions();
	statusBar()->showMessage(tr("DVD informations loaded"), 2000);
}

void MainWindow::saveDvdInfo(const QString &infoFilePath)
{
	QFile file(infoFilePath);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("DVDx InfoTool"),
							 tr("Cannot write file %1:\n%2.")
							 .arg(infoFilePath)
							 .arg(file.errorString()));
		return;
	}

	QTextStream out(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	out << allView->toPlainText();
	QApplication::restoreOverrideCursor();

	statusBar()->showMessage(tr("DVD-Video informations saved"), 2000);
}

void MainWindow::loadDvdTitleInfo(const QString &dvdPath, const int title)
{
	currentDvdTitleInfo = ReadDvdTitleInfo( (const char *) dvdPath.toAscii(), title );

	if ( !currentDvdTitleInfo.valid ) {
		QMessageBox::warning(this, tr("DVDx InfoTool"),
							 tr("Cannot load DVD title informations:\n\n%1\n")
							 .arg(currentDvdTitleInfo.errmsg));
		return;
	}

	stdTitleView->setPath( currentDvdTitleInfo.path );
	stdTitleView->setTitle( currentDvdTitleInfo.title );
	stdTitleView->setVtsN( currentDvdTitleInfo.vtsn );
	stdTitleView->setChapters( currentDvdTitleInfo.chapters );
	stdTitleView->setAngles( currentDvdTitleInfo.angles );
	stdTitleView->setDuration( currentDvdTitleInfo.length );
	stdTitleView->setVideo( currentDvdTitleInfo.video );
	for ( int i = 0; i < 2; i++) {
		stdTitleView->addAudioInfo( i + 1 , "audio DVD blabla");
	}
	for ( int i = 0; i < 4; i++) {
		stdTitleView->addSubtitleInfo( i + 1 , "subtitle DVD blabla");
	}
	
	QString str = currentDvdTitleInfo.text;
	QApplication::setOverrideCursor(Qt::WaitCursor);
	allView->setPlainText( str );
	QApplication::restoreOverrideCursor();

	QString strView = getDvdTitleInfoTextView( str );
	
	QApplication::setOverrideCursor(Qt::WaitCursor);
	txtView->setPlainText( strView );
	QApplication::restoreOverrideCursor();
	
/*
	int currentView = views->currentIndex();
	if ( views->widget(0) != (QWidget *) stdTitleView ) {
		views->removeWidget(stdView);
		views->insertWidget( 0 , stdTitleView );
	}
	views->setCurrentIndex( currentView );
standard view is not available in this version */
	
	setCurrentDvdPath(dvdPath);
	statusBar()->showMessage(tr("DVD title informations loaded"), 2000);
}

void MainWindow::saveDvdTitleInfo(const QString &infoFilePath, const int title)
{



	statusBar()->showMessage(tr("DVD title informations saved"), 2000);
}

void MainWindow::loadDvdVtsInfo(const QString &dvdPath, const int vts)
{
	// TODO: replace with ReadDvdInfo() then getDvdVtsInfo()
	
	currentDvdVtsInfo = ReadDvdVtsInfo( (const char *) dvdPath.toAscii(), vts );

	if ( !currentDvdVtsInfo.valid ) {
		QMessageBox::warning(this, tr("DVDx InfoTool"),
							 tr("Cannot load VTS informations:\n\n%1\n")
							 .arg(currentDvdVtsInfo.errmsg));
		return;
	}

	QString str( currentDvdVtsInfo.text );
	stdTitleView->setPath( currentDvdTitleInfo.path );
	
	QApplication::setOverrideCursor(Qt::WaitCursor);
	allView->setPlainText( str );
	QApplication::restoreOverrideCursor();

	QString strView = getDvdVtsInfoTextView( str );
	
	QApplication::setOverrideCursor(Qt::WaitCursor);
	txtView->setPlainText( strView );
	QApplication::restoreOverrideCursor();
	
/*
	int currentView = views->currentIndex();
	if ( views->widget(0) != (QWidget *) stdTitleView ) {
		views->removeWidget(stdView);
		views->insertWidget( 0 , stdTitleView );
	}
	views->setCurrentIndex( currentView );
standard view is not available in this version */
	
	setCurrentDvdPath(dvdPath);
	statusBar()->showMessage(tr("VTS informations loaded"), 2000);
}

void MainWindow::setCurrentDvdPath(const QString &dvdPath)
{
	curFile = dvdPath;
	if (curFile.isEmpty())
		setWindowTitle(appName);
	else
		setWindowTitle(tr("%1 - %2").arg(appName)
									.arg(curFile));

	QSettings settings("labDV", "DVDx InfoTool");
	QStringList files = settings.value("recentFileList").toStringList();
	files.removeAll(dvdPath);
	files.prepend(dvdPath);
	while (files.size() > MaxRecentFiles)
		files.removeLast();

	settings.setValue("recentFileList", files);

	foreach (QWidget *widget, QApplication::topLevelWidgets()) {
		MainWindow *mainWin = qobject_cast<MainWindow *>(widget);
		if (mainWin)
			mainWin->updateRecentFileActions();
	}
}

void MainWindow::updateRecentFileActions()
{
	QSettings settings("labDV", "DVDx InfoTool");
	QStringList files = settings.value("recentFileList").toStringList();

	int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

	for (int i = 0; i < numRecentFiles; ++i) {
		QString text = tr("&%1 %2").arg(i + 1).arg(strippedName(files[i]));
		recentFileActs[i]->setText(text);
		recentFileActs[i]->setData(files[i]);
		recentFileActs[i]->setVisible(true);
	}
	for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
		recentFileActs[j]->setVisible(false);

	separatorAct->setVisible(numRecentFiles > 0);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}

QString MainWindow::getDvdInfoTextView(const QString &all ) 
{
	QString strSimplified;

	strSimplified = all;
	QRegExp rx( "\\s*Chapter[^\\n]+" );
	rx.setMinimal(false);
	strSimplified.remove(rx);
	rx.setMinimal(true);
	rx.setPattern( "offset.*Video attributes of VTSTT_VOBS" );
	strSimplified.replace(rx, "Video attributes of VTSTT_VOBS");
	rx.setPattern( "(Number of[^\n]*stream)" );
	strSimplified.replace(rx, "  \\1");
	
	return strSimplified;
}

QString MainWindow::getDvdTitleInfoTextView(const QString &all ) 
{
	QString strSimplified;

	strSimplified = all;
	QRegExp rx( "Part of Title.+(PGCI Unit table.+Menu PGCI Unit table)" );
	rx.setMinimal(false);
	strSimplified.replace(rx, "\\1");
	rx.setMinimal(true);
	rx.setPattern( "End byte of VTSI_MAT.*\\n" );
	strSimplified.remove(rx);
	rx.setPattern( "Start sector of.*\\n" );
	strSimplified.remove(rx);
	rx.setPattern( "PGCI Unit table.*----\\n\\n" );
	strSimplified.remove(rx);
	rx.setPattern( "(Next|Prev|GoUp|Still time|PG Playback mode|Color).*\\n" );
	strSimplified.remove(rx);
	rx.setPattern( "(No Command table present|Number of (Pre|Post|Cell) commands).*\\n" );
	strSimplified.remove(rx);
	rx.setPattern( "\\(\\d+\\).*\n" );
	strSimplified.remove(rx);
	rx.setPattern( "\\s+PGC Category:" );
	//strSimplified.replace(rx, "\n- - - - - - - - - -\nPGC Category:");
	strSimplified.replace(rx, "\n~~~~~~~~~~~~~~~~~~\nPGC Category:");
	rx.setPattern( "Time:[^\\n]+VOBU Sector:[^\\n]+(\\d|a|b|c|d|e|f)\\s\\n" ); 
	strSimplified.remove(rx);
	
	return strSimplified;
}

QString MainWindow::getDvdVtsInfoTextView(const QString &all ) 
{
	QString strSimplified;

	strSimplified = all;
	QRegExp rx( "\\s*Chapter[^\\n]+" );
	rx.setMinimal(false);
	strSimplified.remove(rx);
	rx.setMinimal(true);
	rx.setPattern( "offset.*Video attributes of VTSTT_VOBS" );
	strSimplified.replace(rx, "Video attributes of VTSTT_VOBS");
	rx.setPattern( "(Number of[^\n]*stream)" );
	strSimplified.replace(rx, "  \\1");
	
	return strSimplified;
}

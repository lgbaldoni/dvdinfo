/*****************************************************************************
 *
 *  dvdtitleinfoview.h -- Definitions for DVD Title Info view widget
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

#ifndef DVDTITLEINFOVIEW_H_
#define DVDTITLEINFOVIEW_H_

#include <QWidget>
#include <QFont>
#include <QSize>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

#include "dvdinfocore.h"

class DvdTitleInfoView : public QWidget
{
	Q_OBJECT

public:
	DvdTitleInfoView(QWidget *parent = 0);
	void setPath(const char *path);
	void setTitle(const int title);
	void setVtsN(const int vtsn);
	void setChapters(const int chapters);
	void setAngles(const int angles);
	void setDuration(const int seconds);
	void setVideo(const dvdVideo_t video);
	void addAudioInfo(const int track, const char *info);
	void addSubtitleInfo(const int track, const char *info);
	
public slots:

signals:

protected:

private:
	QLabel *pathLabel;
	QLineEdit *pathData;
	QLabel *titleLabel;
	QLineEdit *titleData;
	QLabel *vtsnLabel;
	QLineEdit *vtsnData;
	QLabel *chaptersLabel;
	QLineEdit *chaptersData;
	QLabel *anglesLabel;
	QLineEdit *anglesData;
	QLabel *durationLabel;
	QLineEdit *durationData;
	QLabel *videoLabel;
	QLineEdit *videoData;
	QLabel *audioLabel;
	QTextEdit *audioData;
	QLabel *subtitlesLabel;
	QTextEdit *subtitlesData;
};

#endif /*DVDTITLEINFOVIEW_H_*/

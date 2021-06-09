/*****************************************************************************
 *
 *  dvdtitleinfoview.cpp -- DVD Title Info view widget
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

#include <QtWidgets>
#include <stdint.h>

#include "dvdtitleinfoview.h"

DvdTitleInfoView::DvdTitleInfoView(QWidget *parent)
	: QWidget(parent)
{
	QFont infoFont("Courier");
	infoFont.setStyleHint(QFont::TypeWriter);
	
	pathLabel = new QLabel();
	pathLabel->setText(tr("<b>DVD Title path: </b>"));	
	pathData = new QLineEdit();
	pathData->setReadOnly(true);
	pathData->setText(tr("no DVD-Video title loaded"));

	titleLabel = new QLabel();
	titleLabel->setText(tr("<b>Title: </b>"));	
	titleData = new QLineEdit();
	titleData->setReadOnly(true);
	titleData->setText(tr(""));
	titleData->setMaxLength(2);
	titleData->setMaximumWidth(40);
	
	vtsnLabel = new QLabel();
	vtsnLabel->setText(tr("<b>Video Title Set Number: </b>"));	
	vtsnData = new QLineEdit();
	vtsnData->setReadOnly(true);
	vtsnData->setText(tr(""));
	vtsnData->setMaxLength(2);
	vtsnData->setMaximumWidth(40);
	
	chaptersLabel = new QLabel();
	chaptersLabel->setText(tr("<b>Chapters: </b>"));	
	chaptersData = new QLineEdit();
	chaptersData->setReadOnly(true);
	chaptersData->setText(tr(""));
	chaptersData->setMaxLength(2);
	chaptersData->setMaximumWidth(40);
	
	anglesLabel = new QLabel();
	anglesLabel->setText(tr("<b>Angles: </b>"));	
	anglesData = new QLineEdit();
	anglesData->setReadOnly(true);
	anglesData->setText(tr(""));
	anglesData->setMaxLength(2);
	anglesData->setMaximumWidth(40);
	
	durationLabel = new QLabel();
	durationLabel->setText(tr("<b>Duration: </b>"));	
	durationData = new QLineEdit();
	durationData->setReadOnly(true);
	durationData->setText(tr(""));
	durationData->setMaxLength(8);
	durationData->setMaximumWidth(60);
	
	videoLabel = new QLabel();
	videoLabel->setText(tr("<b>Video: </b>"));	
	videoData = new QLineEdit();
	videoData->setReadOnly(true);
	videoData->setText(tr(""));
	
	audioLabel = new QLabel();
	audioLabel->setText(tr("<b>Audio Tracks: </b>"));	
	audioData = new QTextEdit();
	audioData->setReadOnly(true);
	audioData->setFont(infoFont);
	audioData->setLineWrapMode(QTextEdit::NoWrap);
	audioData->setText(tr("Audio tracks:\n\n"));
	
	subtitlesLabel = new QLabel();
	subtitlesLabel->setText(tr("<b>Video Format: </b>"));	
	subtitlesData = new QTextEdit();
	subtitlesData->setReadOnly(true);
	subtitlesData->setFont(infoFont);
	subtitlesData->setLineWrapMode(QTextEdit::NoWrap);
	subtitlesData->setText(tr("Subtitles:\n\n"));
	
	QHBoxLayout *pathLayout = new QHBoxLayout;
	pathLayout->addWidget(pathLabel);
	pathLayout->addWidget(pathData);
	
	QHBoxLayout *titleLayout = new QHBoxLayout;
	titleLayout->addWidget(titleLabel);
	titleLayout->addWidget(titleData);
	titleLayout->addStretch();
	
	QHBoxLayout *vtsnLayout = new QHBoxLayout;
	vtsnLayout->addWidget(vtsnLabel);
	vtsnLayout->addWidget(vtsnData);
	vtsnLayout->addStretch();
	
	QHBoxLayout *chaptersLayout = new QHBoxLayout;
	chaptersLayout->addWidget(chaptersLabel);
	chaptersLayout->addWidget(chaptersData);
	chaptersLayout->addStretch();
	
	QHBoxLayout *anglesLayout = new QHBoxLayout;
	anglesLayout->addWidget(anglesLabel);
	anglesLayout->addWidget(anglesData);
	anglesLayout->addStretch();
	
	QHBoxLayout *durationLayout = new QHBoxLayout;
	durationLayout->addWidget(durationLabel);
	durationLayout->addWidget(durationData);
	durationLayout->addStretch();
	
	QHBoxLayout *videoLayout = new QHBoxLayout;
	videoLayout->addWidget(videoLabel);
	videoLayout->addWidget(videoData);
	videoLayout->addStretch();
	
	QVBoxLayout *audioLayout = new QVBoxLayout;
	audioLayout->addWidget(audioData);
	audioLayout->addStretch();
	
	QVBoxLayout *subtitlesLayout = new QVBoxLayout;
	subtitlesLayout->addWidget(subtitlesData);
	subtitlesLayout->addStretch();
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(pathLayout);
	mainLayout->addLayout(titleLayout);
	mainLayout->addLayout(vtsnLayout);
	mainLayout->addLayout(chaptersLayout);
	mainLayout->addLayout(anglesLayout);
	mainLayout->addLayout(durationLayout);
	mainLayout->addLayout(videoLayout);
	mainLayout->addLayout(audioLayout);
	mainLayout->addLayout(subtitlesLayout);
	mainLayout->addStretch();
	
	setLayout(mainLayout);
}

void DvdTitleInfoView::setPath(const char *path)
{
	QString str(path);
	pathData->setText(str);
}

void DvdTitleInfoView::setTitle(const int title)
{
	QString str;
	str.setNum(title);
	titleData->setText(str);
}

void DvdTitleInfoView::setVtsN(const int vtsn)
{
	QString str;
	str.setNum(vtsn);
	vtsnData->setText(str);
}

void DvdTitleInfoView::setChapters(const int chapters)
{
	QString str;
	str.setNum(chapters);
	chaptersData->setText(str);
}

void DvdTitleInfoView::setAngles(const int angles)
{
	QString str;
	str.setNum(angles);
	anglesData->setText(str);
}

void DvdTitleInfoView::setDuration(const int seconds)
{
	QString str;
	str.setNum(seconds);
	durationData->setText(str);
}

void DvdTitleInfoView::setVideo(const dvdVideo_t video)
{
	QString str("dvdVideo_t to be done...");
	videoData->setText(str);
}

void DvdTitleInfoView::addAudioInfo(const int track, const char *info)
{
	char *str = new char[ strlen(info) + 40 ];
	sprintf(str, "Audio track %2d\n--------------\n%s\n\n", track, info);
	audioData->append(str);
	delete[] str;
}

void DvdTitleInfoView::addSubtitleInfo(const int track, const char *info)
{
	char *str = new char[ strlen(info) + 40 ];
	sprintf(str, "Subtitle track %2d\n-----------------\n%s\n\n", track, info);
	subtitlesData->append(str);
	delete[] str;
}


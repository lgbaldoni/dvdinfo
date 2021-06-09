/*****************************************************************************
 *
 *  dvdinfoview.cpp -- DVD Info view widget
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

#include "dvdinfoview.h"

DvdInfoView::DvdInfoView(QWidget *parent)
	: QWidget(parent)
{
	QFont infoFont("Courier");
	infoFont.setStyleHint(QFont::TypeWriter);
	
	pathLabel = new QLabel();
	pathLabel->setText(tr("<b>DVD path: </b>"));	
	pathData = new QLineEdit();
	pathData->setReadOnly(true);
	pathData->setText(tr("no DVD-Video loaded"));

	vtsnLabel = new QLabel();
	vtsnLabel->setText(tr("<b>Number of VTS: </b>"));	
	vtsnData = new QLineEdit();
	vtsnData->setReadOnly(true);
	vtsnData->setText(tr(""));
	vtsnData->setMaxLength(2);
	vtsnData->setMaximumWidth(40);
	
	/* Temporarly message */ 
	NoVtsDataLabel = new QLabel();
	NoVtsDataLabel->setText(tr("<i>VTS data isn't available in this version, "
			"please <a href='http://www.labdv.com/dvdx'>check the DVDx InfoTool "
			"updates link</a> for new versions available.</i>"));	
	
	vtsInfoData = new QTextEdit();
	vtsInfoData->setReadOnly(true);
	vtsInfoData->setFont(infoFont);
	vtsInfoData->setLineWrapMode(QTextEdit::NoWrap);
	vtsInfoData->setText(tr("no informations loaded"));
	
	QHBoxLayout *pathLayout = new QHBoxLayout;
	pathLayout->addWidget(pathLabel);
	pathLayout->addWidget(pathData);
	
	QHBoxLayout *vtsnLayout = new QHBoxLayout;
	vtsnLayout->addWidget(vtsnLabel);
	vtsnLayout->addWidget(vtsnData);
	vtsnLayout->addStretch();
	
	QVBoxLayout *vtsInfoLayout = new QVBoxLayout;
	vtsInfoLayout->addWidget(vtsInfoData);
	vtsInfoLayout->addStretch();
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(pathLayout);
	mainLayout->addLayout(vtsnLayout);
	mainLayout->addWidget(NoVtsDataLabel);  /* Temporarly message */ 
	mainLayout->addLayout(vtsInfoLayout);
	mainLayout->addStretch();
	
	setLayout(mainLayout);
}

void DvdInfoView::setPath(const char *path)
{
	QString str(path);
	pathData->setText(str);
}

void DvdInfoView::setVtsN(const int number)
{
	QString str;
	str.setNum(number);
	vtsnData->setText(str);
}

void DvdInfoView::addInfo(const int vts, const char *info)
{
	char *str = new char[ strlen(info) + 40 ];
	sprintf(str, "VTS %2d\n------\n%s\n", vts, info);
	vtsInfoData->append(str);
	delete[] str;
}

void DvdInfoView::resetInfo()
{
	vtsInfoData->clear();
}

/*****************************************************************************
 *
 *  dvdinfoview.h -- Definitions for DVD Info view widget
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

#ifndef DVDINFOVIEW_H_
#define DVDINFOVIEW_H_

#include <QWidget>
#include <QFont>
#include <QSize>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

class DvdInfoView : public QWidget
{
	Q_OBJECT

public:
	DvdInfoView(QWidget *parent = 0);
	void setPath(const char *path);
	void setVtsN(const int number);
	void addInfo(const int vts, const char *info);
	void resetInfo();

public slots:

signals:

protected:

private:
	QLabel *pathLabel;
	QLineEdit *pathData;
	QLabel *vtsnLabel;
	QLineEdit *vtsnData;
	QLabel *NoVtsDataLabel;
	QTextEdit *vtsInfoData;
};

#endif /*DVDINFOVIEW_H_*/

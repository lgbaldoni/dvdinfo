/*****************************************************************************
 *
 *  stdviewwidget.h -- Core definition for DVD Info in DVDInfoCore namespace
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

#ifndef DVDINFOCORE_H_
#define DVDINFOCORE_H_
#include <stdint.h>
#include <dvdread/dvd_reader.h>
#include <dvdread/ifo_types.h>

#ifndef MAX_PATH
#define MAX_PATH 250
#endif

#define DVDINFOCORE_TEXTSIZE 16000
#define DVDINFOCORE_ERRMSGSIZE 400
#define DVDINFOCORE_ZONESEP "\n                       ============\n\n"

#ifdef QT_NO_DEBUG
#define READERSIZE 2000000		// 2MB is very large but necessary for many titles
#else
#define READERSIZE 100000		// 2MB is too large for gcc debugger
#endif

typedef struct dvdVideo {
	int type;					// mpeg1, mpeg2
} dvdVideo_t;

typedef struct ascpectRatio {
	int code;
	double width;					// always 1
	double height;
} ascpectRatio_t;

typedef struct tvStd {
	int type;					// mpeg1, mpeg2
} tvStd_t;

typedef struct dvdAudio {
	int type;					// AC3, MEPG2, PCM
	bool vbr;					// variable bit rate
	int bitrate;				//
} dvdAudio_t;

typedef struct dvdSubtitle {
	int type;
} dvdSubtitle_t;

typedef struct dvdTitleInfo {
	char path[MAX_PATH];		// path to IFO folder
	int title;					// title number (so is title index + 1)
	int vtsn;					// title is part of this VTS
	int chapters;
	int angles;
	int length;					// title length in seconds
	dvdVideo_t video;			// video format
	dvdAudio_t audio[8];		// audio tracks
	dvdSubtitle_t subtitle[99];	// subtitles
	char text[READERSIZE];		// DVD title informations in Plain Text
	bool valid;					// true if this structure content is valid
	char errmsg[DVDINFOCORE_ERRMSGSIZE];			// error message if structure is not valid
} dvdTitleInfo_t;

typedef struct dvdVtsInfo {
	char path[MAX_PATH];		// path to IFO folder
	int set;					// VTS num (from 1 to vtsn)
	int titles;					// number of titles in the VTS
	int pgcnum;					// number of PGC in the VTS
	int cellnum;				// number of VOB cells in the VTS
	int longtitlenum;			// longest title (from 1)
	int longpgcnum;				// longest PGC index (from 1 to pgcnum)
	int longpgctime;			// longest PGC duration in seconds
	char text[DVDINFOCORE_TEXTSIZE];			// VTS informations in Plain Text
	bool valid;					// true if this structure content is valid
	char errmsg[DVDINFOCORE_ERRMSGSIZE];			// error message if structure is not valid
} dvdVtsInfo_t;

typedef struct dvdInfo {
	char path[MAX_PATH];		// path to IFO folder
	int titles;					// number of titles
	int vtsnum;					// number of VTS
	char text[DVDINFOCORE_TEXTSIZE];			// DVD informations in Plain Text
	bool valid;					// true if this structure content is valid
	char errmsg[DVDINFOCORE_ERRMSGSIZE];			// error message if structure is not valid
} dvdInfo_t;

namespace DvdInfoCore {

dvdInfo ReadDvdInfo( const char *dvdpath );
dvdTitleInfo ReadDvdTitleInfo( const char *dvd_path, const int title );
dvdVtsInfo ReadDvdVtsInfo( const char *dvd_path, const int vts );
void SprintVideoAttributes(char *str, video_attr_t *attr);

} // namespace DVDInfoCore

#endif /*DVDINFOCORE_H_*/

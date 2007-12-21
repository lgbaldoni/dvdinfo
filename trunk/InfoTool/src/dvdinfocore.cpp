/*****************************************************************************
 *
 *  dvdinfocore.cpp -- Core DVD Info application
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

#include "/rd/src/libdvdread-0.9.7/config.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#if defined(HAVE_INTTYPES_H)
#include <inttypes.h>
#elif defined(HAVE_STDINT_H)
#include <stdint.h>
#endif

#if !defined(UINT8_MAX) || !defined(UINT16_MAX) || !defined(INT32_MAX)
#error "Must include <inttypes.h> or <stdint.h> before any libdvdread header."
#endif

#include <dvdread/dvd_reader.h>
#include <dvdread/ifo_types.h>
#include <dvdread/ifo_print.h>
#include <dvdread/ifo_read.h>
//#include <dvdcss/dvdcss.h>

#include <cstring>
#include <iostream>
#include <sstream>

#include "dvdinfocore.h"

#define READ_STDOUT	\
	strncpy( reader, outbuf, READERSIZE );	\
	strcat( titleInfo.text, reader );		\
	fflush( stdout );						\
	memset( outbuf, '\0', READERSIZE );
	
#define RETURN_TITLEINFO \
	if ( ifohandle ) {			\
		ifoClose( ifohandle );	\
	}							\
	if ( dvd ) {				\
		DVDClose( dvd );		\
		DVDFinish();			\
	}							\
	delete[] outbuf;			\
	delete[] reader;			\
	return titleInfo;

	
namespace DvdInfoCore {


dvd_reader_t *dvd = 0;
ifo_handle_t *ifo_file = 0;
tt_srpt_t *tt_srpt = 0;
vts_attributes_t *vts_atrt = 0;

int i, j;

bool NoText = false;	// set to true to fill the text field in info structures

dvdInfo ReadDvdInfo( const char *dvd_path )
{
	dvdInfo info;
	char buff[4000];
	
	dvd = DVDOpen( dvd_path );
	if( !dvd ) {
		info.valid = false;
		sprintf( info.errmsg, "- can't open DVD at %s", dvd_path );
		return info;
	}

	ifo_file = ifoOpen( dvd, 0 );
	if( !ifo_file ) {
		info.valid = false;
		sprintf( info.errmsg, "- can't open VMG info" );
		DVDClose( dvd );
		DVDFinish();
		return info;
	}
	tt_srpt = ifo_file->tt_srpt;
	//vts_atrt = ifo_file->vts_atrt;

	/*
	 * Fill in the dvdinfo structure
	 */
	
	if ( tt_srpt ) {
		info.titles = tt_srpt->nr_of_srpts;	
	}
	
	if ( ifo_file->vts_atrt ) {
		info.vtsnum = ifo_file->vts_atrt->nr_of_vtss;
	}
	
/*
	int longtitlenum = 0;
	int longpgcnum = 0;
	int longpgctime = 0;
	for ( i = 1; i < vts_atrt->nr_of_vtss ) {
		if ( ) {
			longtitlenum = 0;
			longpgcnum = 0;
			longpgctime = 0;		
		}		
	}
*/
	
	/*
	 * Build the text info
	 */
	
	::strncpy( info.path, dvd_path, MAX_PATH ); 
	sprintf( info.text, "DVD-Video Disc Informations: %s\n\n", dvd_path );

	sprintf( buff, "There are %d titles.\n", tt_srpt->nr_of_srpts );
	strcat( info.text, buff );

	for( i = 0; i < tt_srpt->nr_of_srpts; ++i ) {
		ifo_handle_t *vts_file;
		vts_ptt_srpt_t *vts_ptt_srpt;
		pgc_t *cur_pgc;
		int vtsnum, ttnnum, pgcnum, chapts;
	
		vtsnum = tt_srpt->title[ i ].title_set_nr;
		ttnnum = tt_srpt->title[ i ].vts_ttn;
		chapts = tt_srpt->title[ i ].nr_of_ptts;
	
		sprintf( buff, "\nTitle %d:\n", i + 1 );
		strcat( info.text, buff );
		sprintf( buff, "\tIn VTS: %d [TTN %d]\n", vtsnum, ttnnum );
		strcat( info.text, buff );
		sprintf( buff, "\n" );
		sprintf( buff, "\tTitle has %d chapters and %d angles\n", chapts,
				tt_srpt->title[ i ].nr_of_angles );
		strcat( info.text, buff );
		
		vts_file = ifoOpen( dvd, vtsnum );
		if( !vts_file ) {
			info.valid = false;
			sprintf( info.errmsg, "- can't open info file for title %d", vtsnum );
			DVDClose( dvd );
			DVDFinish();
			return info;}

		vts_ptt_srpt = vts_file->vts_ptt_srpt;
		for( j = 0; j < chapts; ++j ) {
			int start_cell;
			int pgn;

			pgcnum = vts_ptt_srpt->title[ ttnnum - 1 ].ptt[ j ].pgcn;
			pgn = vts_ptt_srpt->title[ ttnnum - 1 ].ptt[ j ].pgn;
			cur_pgc = vts_file->vts_pgcit->pgci_srp[ pgcnum - 1 ].pgc;
			start_cell = cur_pgc->program_map[ pgn - 1 ] - 1;
	
			sprintf( buff, "\tChapter %3d [PGC %2d, PG %2d] starts at Cell %2d [sector %x-%x]\n",
					j, pgcnum, pgn, start_cell,
					cur_pgc->cell_playback[ start_cell ].first_sector,
					cur_pgc->cell_playback[ start_cell ].last_sector );
			strcat( info.text, buff );
		}

		ifoClose( vts_file );
	}

	ifoClose( ifo_file );	
	DVDClose( dvd );
	DVDFinish(); //to keep memory checkers from complaining
	
	info.valid = true;
	return info;
}

dvdTitleInfo ReadDvdTitleInfo( const char *dvd_path, int title )
{
	dvdTitleInfo titleInfo;
	char *outbuf;
	char *reader;
	ifo_handle_t *ifohandle = 0;
	
	// title index is title - 1
	int i = title - 1;
	
	// we must route ifo_print outputs to our buffer (ifo_print.c from libdvdread)
	outbuf = new char[READERSIZE];
	reader = new char[READERSIZE];
	if ( setvbuf(stdout, outbuf, _IOFBF, READERSIZE) != 0 ) {
		titleInfo.valid = false;
		sprintf( titleInfo.errmsg, "- can't buffer and get output from ifo_print utility" );
		RETURN_TITLEINFO
	}
	fflush( stdout );
	memset( outbuf, '\0', READERSIZE );
	
	dvd = DVDOpen( dvd_path );
	if( !dvd ) {
		titleInfo.valid = false;
		sprintf( titleInfo.errmsg, "- can't open DVD at %s", dvd_path );
		RETURN_TITLEINFO
	}
	
	ifohandle = ifoOpen(dvd, title);
	if ( !ifohandle ) {
		titleInfo.valid = false;
		sprintf( titleInfo.errmsg, "- can't open IFO file for title %d at %s", title, dvd_path );
		RETURN_TITLEINFO
	}
	tt_srpt = ifohandle->tt_srpt;

	/*
	 * Fill in the dvdinfo structure
	 */
	
	if ( tt_srpt ) {
		titleInfo.chapters = tt_srpt->title[ i ].nr_of_ptts;
		titleInfo.angles = tt_srpt->title[ i ].nr_of_angles;
	}
	
	//SprintVideoAttributes(&vtsi_mat->vtsm_video_attr);

	/*
	 * Build the text info
	 */

	::strncpy( titleInfo.path, dvd_path, MAX_PATH ); 
	titleInfo.title = title;
	sprintf( titleInfo.text, "DVD-Video Informations: Title %d\n\nPath is %s\n\n", title, dvd_path );

	if ( ifohandle->vmgi_mat ) {

		strcat( titleInfo.text, "VMG top level\n-------------\n" );
		ifoPrint_VMGI_MAT(ifohandle->vmgi_mat);
		READ_STDOUT
		
		strcat( titleInfo.text, "\nFirst Play PGC\n--------------\n" );
		if ( ifohandle->first_play_pgc ) {
			ifoPrint_PGC(ifohandle->first_play_pgc);
			READ_STDOUT
			
		} else {
			strcat( titleInfo.text, "No First Play PGC present\n" );
		}

		strcat( titleInfo.text, "\nTitle Track search pointer table\n" );
		strcat( titleInfo.text, "------------------------------------------------\n" );
		ifoPrint_TT_SRPT(ifohandle->tt_srpt);
		READ_STDOUT

		strcat( titleInfo.text, "\nMenu PGCI Unit table\n" );
		strcat( titleInfo.text, "--------------------\n" );
		if ( ifohandle->pgci_ut ) {
			ifoPrint_PGCI_UT(ifohandle->pgci_ut);
			READ_STDOUT
		} else {
			strcat( titleInfo.text, "No PGCI Unit table present\n" );
		}

		strcat( titleInfo.text, "\nParental Manegment Information table\n" );
		strcat( titleInfo.text, "------------------------------------\n" );
		if ( ifohandle->ptl_mait ) {
			ifoPrint_PTL_MAIT(ifohandle->ptl_mait);
			READ_STDOUT
		} else {
			strcat( titleInfo.text, "No Parental Management Information present\n" );
		}

		strcat( titleInfo.text, "\nVideo Title Set Attribute Table\n" );
		strcat( titleInfo.text, "-------------------------------\n" );
		ifoPrint_VTS_ATRT(ifohandle->vts_atrt);
		READ_STDOUT
		
		strcat( titleInfo.text, "\nText Data Manager Information\n" );
		strcat( titleInfo.text, "-----------------------------\n" );
		if ( ifohandle->txtdt_mgi ) {
			// next one isn't imlplemented yet
			// ifoPrint_TXTDT_MGI(&(vmgi->txtdt_mgi));
			// READ_STDOUT
		} else {
			strcat( titleInfo.text, "No Text Data Manager Information present\n" );
		}

		strcat( titleInfo.text, "\nMenu Cell Adress table\n" );
		strcat( titleInfo.text, "-----------------\n" );
		if ( ifohandle->menu_c_adt ) {
			ifoPrint_C_ADT(ifohandle->menu_c_adt);
			READ_STDOUT
		} else {
			strcat( titleInfo.text, "No Menu Cell Adress table present\n" );
		}

		strcat( titleInfo.text, "\nVideo Manager Menu VOBU address map\n" );
		strcat( titleInfo.text, "-----------------\n" );
		if ( ifohandle->menu_vobu_admap ) {
			ifoPrint_VOBU_ADMAP(ifohandle->menu_vobu_admap);
			READ_STDOUT
		} else {
			strcat( titleInfo.text, "No Menu VOBU address map present\n" );   
		}
	  }

	if ( ifohandle->vtsi_mat ) {
		
		strcat( titleInfo.text, "VTS top level\n-------------\n" );
		ifoPrint_VTSI_MAT(ifohandle->vtsi_mat);
		READ_STDOUT
		
		strcat( titleInfo.text, "\nPart of Title Track search pointer table\n" );
		strcat( titleInfo.text, "----------------------------------------------\n" );
		ifoPrint_VTS_PTT_SRPT(ifohandle->vts_ptt_srpt);
		READ_STDOUT
		
		strcat( titleInfo.text, "\nPGCI Unit table\n" );
		strcat( titleInfo.text, "--------------------\n" );
		ifoPrint_PGCIT(ifohandle->vts_pgcit);
		READ_STDOUT

		strcat( titleInfo.text, "\nMenu PGCI Unit table\n" );
		strcat( titleInfo.text, "--------------------\n" );
		if(ifohandle->pgci_ut) {
			ifoPrint_PGCI_UT(ifohandle->pgci_ut);
			READ_STDOUT
		} else {
			strcat( titleInfo.text, "No Menu PGCI Unit table present\n" );
		}
		
		strcat( titleInfo.text, "\nTime Search table\n" );
		strcat( titleInfo.text, "-----------------\n" );
		if(ifohandle->vts_tmapt) {
			ifoPrint_VTS_TMAPT(ifohandle->vts_tmapt);
			READ_STDOUT
		} else {
			strcat( titleInfo.text, "No Time Search table present\n" );
		}

		strcat( titleInfo.text, "\nMenu Cell Adress table\n" );
		strcat( titleInfo.text, "-----------------\n" );
		if(ifohandle->menu_c_adt) {
			ifoPrint_C_ADT(ifohandle->menu_c_adt);
			READ_STDOUT
		} else {
			strcat( titleInfo.text, "No Cell Adress table present\n" );
		}

		strcat( titleInfo.text, "\nVideo Title Set Menu VOBU address map\n" );
		strcat( titleInfo.text, "-----------------\n" );
		if(ifohandle->menu_vobu_admap) {
			ifoPrint_VOBU_ADMAP(ifohandle->menu_vobu_admap);
			READ_STDOUT
		} else {
			strcat( titleInfo.text, "No Menu VOBU address map present\n" );
		}

		strcat( titleInfo.text, "\nCell Adress table\n" );
		strcat( titleInfo.text, "-----------------\n" );
		ifoPrint_C_ADT(ifohandle->vts_c_adt);
		READ_STDOUT

		strcat( titleInfo.text, "\nVideo Title Set VOBU address map\n" );
		strcat( titleInfo.text, "-----------------\n" );
		ifoPrint_VOBU_ADMAP(ifohandle->vts_vobu_admap);
		READ_STDOUT
	}

	fflush( stdout );
	setvbuf( stdout, 0, _IONBF, 0 );  // stdout no longer buffered
	
	titleInfo.valid = true;
	RETURN_TITLEINFO
}

void SprintVideoAttributes(char *str, video_attr_t *attr) {
  
	// printf code adapted from ifoPrint_audio_attributes() in libdvdread
	
	char buf[50];
	strcpy(str, "");
	
	/* The following test is shorter but not correct ISO C,
     memcmp(attr,my_friendly_zeros, sizeof(video_attr_t)) */
	if(attr->mpeg_version == 0 
		 && attr->video_format == 0 
		 && attr->display_aspect_ratio == 0 
		 && attr->permitted_df == 0 
		 && attr->unknown1 == 0 
		 && attr->line21_cc_1 == 0 
		 && attr->line21_cc_2 == 0 
		 && attr->bit_rate == 0 
		 && attr->video_format == 0 
		 && attr->letterboxed == 0 
		 && attr->film_mode == 0) {
		strcat(str, "-- Unspecified --");
		return;
	}
	
	switch(attr->mpeg_version) {
	case 0:
		strcat(str, "mpeg1 ");
		break;
	case 1:
		strcat(str, "mpeg2 ");
		break;
	default:
		strcat(str, "(please send a bug report) ");
	}
	
	switch(attr->video_format) {
	case 0:
		strcat(str, "ntsc ");
		break;
	case 1:
		strcat(str, "pal ");
		break;
	default:
		strcat(str, "(please send a bug report) ");
	}
	
	switch(attr->display_aspect_ratio) {
	case 0:
		strcat(str, "4:3 ");
		break;
	case 3:
		strcat(str, "16:9 ");
		break;
	default:
		strcat(str, "(please send a bug report) ");
	}
	
	// Wide is allways allowed..!!!
	switch(attr->permitted_df) {
	case 0:
		strcat(str, "pan&scan+letterboxed ");
		break;
	case 1:
		strcat(str, "only pan&scan "); //??
		break;
	case 2:
		strcat(str, "only letterboxed ");
		break;
	case 3:
		// not specified
		break;
	default:
		strcat(str, "(please send a bug report)");
	}
	
	sprintf(buf, "U%x ", attr->unknown1);
	strcat(str, buf);
	//CHECK_VALUE(!attr->unknown1);
	
	if(attr->line21_cc_1 || attr->line21_cc_2) {
		strcat(str, "NTSC CC ");
		if(attr->line21_cc_1)
			strcat(str, "1 ");
		if(attr->line21_cc_2)
			strcat(str, "2 ");
	}

	switch(attr->bit_rate) {
	case 0:
		strcat(str, "Variable Bit Rate ");
		break;
	case 1:
		strcat(str, "Constant Bit Rate ");
		break;
	default:
		strcat(str, "(please send a bug report)");
	}
	
	{
		int height = 480;
		if(attr->video_format != 0) 
			height = 576;
		switch(attr->picture_size) {
		case 0:
			sprintf(buf, "720x%d ", height);
			strcat(str, buf);
			break;
		case 1:
			sprintf(buf, "704x%d ", height);
			strcat(str, buf);
			break;
		case 2:
			sprintf(buf, "352x%d ", height);
			strcat(str, buf);
			break;
		case 3:
			sprintf(buf, "352x%d ", height/2);
			strcat(str, buf);
			break;			
		default:
			strcat(str, "(please send a bug report) ");
		}
	}

	if(attr->letterboxed) {
		strcat(str, "source letterboxed ");
	}
	
	if(attr->film_mode) {
		strcat(str, "film");
	} else {
		strcat(str, "video"); //camera
	}
}

} // namespace DVDInfoCore

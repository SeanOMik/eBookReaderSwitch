/* BLUnZip
 *	C++ class for doing basic zip extraction to strings
 *	Scott Lawrence  yorgle@gmail.com
 *
 * This code is HEAVILY based on the "minizip" code included with zlib
 * also available here: http://www.winimage.com/zLibDll/minizip.html
 *
 * v1.0 2013-June-05 - Initial release
 */

/* This code is provided under an MIT license:

The MIT License (MIT)

Copyright (c) 2013 Scott Lawrence

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/


#include <iostream>

extern "C"
{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>

#ifdef _WIN32
# include <direct.h>
# include <io.h>
#else
# include <unistd.h>
# include <utime.h>
#endif


#include "minizip/zip.h"
#include "minizip/unzip.h"

#define CASESENSITIVITY (0)
#define WRITEBUFFERSIZE (8192)
#define MAXFILENAME (256)

#ifdef _WIN32
#define USEWIN32IOAPI
#include "minizip/iowin32.h"
#endif
}


#include "BLUnZip.h"


BLUnZip::BLUnZip( std::string _filename )
	: filename( _filename )
	, valid( false )
{
	// make sure it exists
	//if( !ZipFileExists( (char *) _filename.c_str() )) return;

	// open it
	this->zf = this->Open( _filename ); //, ZipFlag_Append );
	if( !this->zf ) return;

	// we're AOK
	valid = true;
}

void BLUnZip::Close( void )
{
	unzClose( this->zf );
	this->zf = NULL;
	this->valid = false;
}

zipFile BLUnZip::Open( std::string zipfilename )
{
	char filename_try[MAXFILENAME+16] = "";
	zipFile zf = NULL;


#        ifdef USEWIN32IOAPI
        zlib_filefunc64_def ffunc;
#        endif

        strncpy(filename_try, zipfilename.c_str(),MAXFILENAME-1);
        /* strncpy doesnt append the trailing NULL, of the string is too long. */
        filename_try[ MAXFILENAME ] = '\0';

#        ifdef USEWIN32IOAPI
        fill_win32_filefunc64A(&ffunc);
        zf = unzOpen2_64(zipfilename.c_str(),&ffunc);
#        else
        zf = unzOpen64(zipfilename.c_str());
#        endif
        if (zf==NULL)
        {
            strcat(filename_try,".zip");
#            ifdef USEWIN32IOAPI
            zf = unzOpen2_64(filename_try,&ffunc);
#            else
            zf = unzOpen64(filename_try);
#            endif
        }

	return zf;

}

BLUnZip::~BLUnZip( void )
{
	this->Close();
}


////////////////////////////////////////////////////////////////////////////////

int BLUnZip::ItemCount( void )
{
	int i = 0;
	unzGoToFirstFile( zf );
	
	do {
		i++;
	} while( (unzGoToNextFile( zf )) == UNZ_OK );

	return i;
}

void BLUnZip::List( void )
{
	int i = 0;

	std::cout << "Listing:" << std::endl;
	for( i=0 ; i<this->ItemCount() ; i++ ) {
		std::string n = this->NameOfItem( i );
		long sz = this->SizeOfItem( i );

		std::cout << "    " << i << ": " << n << "     " << sz << std::endl;
		
	}
}

int BLUnZip::IndexOfItem( std::string itemName )
{
	int i = 0;

	for( i=0 ; i<this->ItemCount() ; i++ ) {
		std::string n = this->NameOfItem( i );

		if( !n.compare( itemName )) return i;
	}
	return -1;
}

void BLUnZip::ListOfItems( std::vector<std::string>& listing )
{
	unzGoToFirstFile( zf );

	listing.clear();
	do {
		char filename_inzip[256];
		unz_file_info64 file_info;
		int err;

		err = unzGetCurrentFileInfo64(zf, &file_info,
			filename_inzip,sizeof(filename_inzip),
			//buf, bufsz,
			NULL,0,NULL,0);
		if (err!=UNZ_OK) return;

		std::string s( filename_inzip );
		listing.push_back( s );
	} while( (unzGoToNextFile( zf )) == UNZ_OK );
}

std::string BLUnZip::NameOfItem( int idx )
{
	std::string ret( "" );
	int i = 0;
	unzGoToFirstFile( zf );
	
	do {
		char filename_inzip[256];
		unz_file_info64 file_info;
		int err;

		err = unzGetCurrentFileInfo64(zf,&file_info,
			filename_inzip,sizeof(filename_inzip),
			//buf, bufsz,
			NULL,0,NULL,0);
		if (err!=UNZ_OK)
		{
                	return ret;
		}
		if( i == idx ) {
			ret.assign( filename_inzip );
			return ret;
		}
		i++;
	} while( (unzGoToNextFile( zf )) == UNZ_OK );

	return ret;
}

long BLUnZip::SizeOfItem( int idx )
{
	int i = 0;
	unzGoToFirstFile( this->zf );
	
	do {
		char filename_inzip[256];
		unz_file_info64 file_info;
		int err;

		err = unzGetCurrentFileInfo64(this->zf,&file_info,
			filename_inzip,sizeof(filename_inzip),
			NULL,0,NULL,0);
		if (err!=UNZ_OK)
		{
			return 0;
		}
		if( i == idx ) {
			return file_info.uncompressed_size;
		}
		i++;
	} while( (unzGoToNextFile( this->zf )) == UNZ_OK );

	return 0;
}


////////////////////////////////////////////////////////////////////////////////
// get the content to RAM
int BLUnZip::ExtractToRAM( int idx, char * buf, long bufsz, std::string pw )
{
	const char * password = NULL; // TODO: password!
	int i = 0;
	int err = 0;

	if( !buf ) return -1;
	buf[0] = '\0';

	if( pw.compare( "" ) ) {
		password = pw.c_str();
	}
	
	unzGoToFirstFile( this->zf );
	
	do {
		if( i == idx ) {
			//err = unzOpenCurrentFile( this->zf );
        		err = unzOpenCurrentFilePassword(this->zf,password);
                	err = unzReadCurrentFile(this->zf,buf,bufsz);
			unzCloseCurrentFile( this->zf );
			return err;
		}
		i++;
	} while( (unzGoToNextFile( this->zf )) == UNZ_OK );

	return 0;
}

std::string BLUnZip::ExtractToString( int idx, std::string password )
{
	long sz = this->SizeOfItem( idx );
	if( sz == 0 ) return "";

	sz++; // for null
	sz *= sizeof( char );
	char * buf = (char *)malloc( sz );

	this->ExtractToRAM( idx, buf, sz, password ); 
	buf[ sz-1 ] = '\0'; // force.

	std::string ret( buf );
	return ret;
}


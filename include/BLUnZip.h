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
#include <vector>

extern "C"
{
#include "minizip/zip.h"
}

class BLUnZip
{
private:
	std::string filename;
	bool valid;
	zipFile zf;

public:
	BLUnZip( std::string filename );
	~BLUnZip( void );

public: 
	bool isValid( void ) { return valid; }

public:
	zipFile Open( std::string zipfilename );
	void Close( void );

/*
public:
	void Add( std::string contentPath, std::string zipPath, int flags );
*/
	
public:
	void List( void );


	int ItemCount( void );

	int IndexOfItem( std::string itemName );

	void ListOfItems( std::vector<std::string>& listing );
	std::string NameOfItem( int idx );
	long SizeOfItem( int idx );
	int ExtractToRAM( int idx, char * buf, long bufsz, std::string pw="" );
	std::string ExtractToString( int idx, std::string password="" );

public:
	long SizeOfItem( std::string itemName ) { return this->SizeOfItem( this->IndexOfItem( itemName)); }
	std::string ExtractToString( std::string itemName, std::string password="" ) { return this->ExtractToString( this->IndexOfItem( itemName), password); }
};

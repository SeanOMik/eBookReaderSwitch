/* BLZip
 *	C++ class for doing basic zip compression
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
#include "minizip/zip.h"
#include "minizip/unzip.h"
}

#define ZipFlag_Overwrite       0x01    /* -o */
#define ZipFlag_Append          0x02    /* -a */
#define ZipFlag_Store           0x04    /* -0 */
#define ZipFlag_Faster          0x08    /* -1 */
#define ZipFlag_Better          0x10    /* -9 */
#define ZipFlag_NoPaths         0x20    /* -j */


class BLZip
{
private:
	std::string filename;
	bool valid;
	zipFile zf;

public:
	BLZip( std::string filename );
	~BLZip( void );

public:
	zipFile Open( std::string zipfilename );
	void Close( void );

public:
	int Add( std::string contentPath,
		  std::string zipPath="",
		  int flags = ZipFlag_Better );
};

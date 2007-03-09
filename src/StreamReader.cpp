/***********************************************************************
** StreamReader.cpp                                                   **
**                                                                    **
** This file is part of dvisvgm -- the DVI to SVG converter           **
** Copyright (C) 2005-2007 Martin Gieseking <martin.gieseking@uos.de> **
**                                                                    **
** This program is free software; you can redistribute it and/or      **
** modify it under the terms of the GNU General Public License        **
** as published by the Free Software Foundation; either version 2     **
** of the License, or (at your option) any later version.             **
**                                                                    **
** This program is distributed in the hope that it will be useful,    **
** but WITHOUT ANY WARRANTY; without even the implied warranty of     **
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the      **
** GNU General Public License for more details.                       **
**                                                                    **
** You should have received a copy of the GNU General Public License  **
** along with this program; if not, write to the Free Software        **
** Foundation, Inc., 51 Franklin Street, Fifth Floor,                 **
** Boston, MA 02110-1301, USA.                                        **
***********************************************************************/
// $Id$

#include "StreamReader.h"
#include "macros.h"

using namespace std;

StreamReader::StreamReader (istream &s) 
	: is(&s)
{
}

/** Reads an unsigned integer from assigned input stream. 
 *  @param bytes number of bytes to read (max. 4)
 *  @return read integer */
UInt32 StreamReader::readUnsigned (int bytes) {
	UInt32 ret = 0;
	for (int i=bytes-1; i >= 0 && !is->eof(); i--) {
		UInt32 b = is->get();
		ret |= b << (8*i);
	}
	return ret;
}


/** Reads an signed integer from assigned input stream. 
 *  @param bytes number of bytes to read (max. 4)
 *  @return read integer */
UInt32 StreamReader::readSigned (int bytes) {
	Int32 ret = is->get();
	if (ret & 128)        // negative value?
		ret |= 0xffffff00;
	for (int i=bytes-2; i >= 0 && !is->eof(); i--) 
		ret = (ret << 8) | is->get();
	return ret;
}


string StreamReader::readString (int length) {
	if (!is)
		throw StreamReaderException("no stream assigned");
	char *buf = new char[length+1];
	if (length > 0)
		is->get(buf, length+1);  // reads 'length' bytes (pos. length+1 is set to 0)
	else
		*buf = 0;
	string ret = buf;
	delete [] buf;
	return ret;
}


/*_LICENCE_BLOCK_
------------------------------------------------------------------
This source file is part of Morrowind Remake

Copyright (c) 2007 Jacob Essex
Also see acknowledgements in the readme

Morrowind Remake is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Morrowind Remake is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.


You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/licenses/gpl.txt

------------------------------------------------------------------
_LICENCE_BLOCK_*/
#include "ESSubString.h"

using namespace ES3;

std::string ESSubString::get(){
	return mSubStr;
}

void ESSubString::set(const std::string &s){
	mRecordSize = (long) s.length();
	mSubStr = s;
}

void ESSubString::read(std::ifstream &ifs){

	//read the size of the string
	ifs.read ((char *)&mRecordSize, sizeof(long));

	char* tSubStr;
	tSubStr = new char[mRecordSize + 4];
	ifs.read(tSubStr, mRecordSize);
	tSubStr[mRecordSize] = '\0';
	mSubStr = tSubStr;
	delete [] tSubStr;

}

void ESSubString::write(std::ofstream &ofs){
	long len = (long) mSubStr.length();
	ofs.write((char*)&len, 4);
	ofs.write(mSubStr.c_str(), (std::streamsize)mSubStr.length());
}
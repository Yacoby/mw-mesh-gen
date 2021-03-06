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
#ifndef _ESSUBREFDATA_H_
#define _ESSUBREFDATA_H_

#include "ESSubRecord.h"
namespace ES3{
/**
* Contains ESRef Position Data (24 bytes), found within a cell record...
*/
struct ESRefData{

	//position data
	float mXPos;
	float mYPos;
	float mZPos;

	//rotation data
	float mXRotate;
	float mYRotate;
	float mZRotate;
};

/**
* Contains the following data relating to info on a cell record:
*			float XPos
*			float YPos
*			float ZPos
*			float XRotate
*			float YRotate
*			float ZRotate
*
*	FYI it is a DATA block
*/


class ESSubRefData : public ESSubRecord{
public:
	/**
	* Gets the data record casted to the correct type
	*/
	ESRefData* getData(){
		return (ESRefData*)mData.c_str(); 
	}

	/**
	* Returns the x position of the object
	*/
	float getXPos(){ return getData()->mXPos; }

	/**
	* Returns the y position of the object
	*/
	float getYPos(){ return getData()->mYPos; }

	/**
	* Returns the z position of the object
	*/
	float getZPos(){ return getData()->mZPos; }

	float getXRot(){ return getData()->mXRotate; }
	float getYRot(){ return getData()->mYRotate; }
	float getZRot(){ return getData()->mZRotate; }
};
}
#endif
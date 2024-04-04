#ifndef _ESLAND_H_
#define _ESLAND_H_

#include <cmath>
#include <memory>
#include <vector>
#include <fstream>

#include <boost/multi_array.hpp>

#include "ESRecord.h"

#define PI 3.14159265


namespace ES3 {

/**
* Used for holding the position in the cell grid of a land record
*/
    struct LandSquare {
        uint32_t cellX;
        uint32_t cellY;
    };


/**
*	Simple vector3 implementation. This removes the depandance on any other library that implements this (Ogre, Niflib)
*/
    struct Vector3 {
        float x;
        float y;
        float z;

        Vector3() {
            x = 0;
            y = 0;
            z = 0;
        }
    };

    class ESLand;

    typedef std::shared_ptr<ESLand> ESLandRef;

/**
*	Holds a LAND record.
*/

    class ESLand : public ESRecord {


        boost::multi_array<uint16_t, 2> mLandTextures;
        /**
        * height data
        * The height data is not absolute values but uses differences between adjacent pixels.
        * Thus a pixel value of 0 means it has the same height as the last pixel. Note that
        * the y-direction of the data is from the bottom up.
        */
        boost::multi_array<int, 2> mHeightData;

        /**
        * The data on where in the world the cell is
        */
        LandSquare mLandSquare;

    public:

        ESLand();


        const boost::multi_array<uint16_t, 2>& getLandTextures() { return mLandTextures; }

        void loadVtexRecord(std::ifstream &ifs);

        void loadVhgtRecord(std::ifstream &ifs);

        float _temp(float x, int y) {
            while (x > y) x -= y;
            while (x < -y) x += y;
            return x;
        }

        int _temp2(float x, float y) {
            int z = 0;
            while (x > 0) {
                x -= y;
                z++;
            }
            return z;
        }

        float getHeightAt(float x, float y);

        ES3::Vector3 getAngleAt(float x, float y);


        /**
        *	@return Details about what swuare the land is on
        */
        const LandSquare& getLandPos() { return mLandSquare; }

        void read(std::ifstream &ifs, long recordSize);
    };

}//nspace

#endif
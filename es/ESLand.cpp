#include "ESLand.h"

using namespace ES3;

ESLand::ESLand() {

    if (mHeightData.size() < 65) {
        mHeightData.resize(65);
        for (int i = 0; i < 65; i++) mHeightData.at(i).resize(65, -256);
    }

    if (mLandTextures.size() < 16) {
        mLandTextures.resize(16);
        for (int x = 0; x < 16; x++) {
            mLandTextures.at(x).resize(16, 0);
            mLandTextures.at(x).at(0) = 0;
        }
    }
}

void ESLand::loadVtexRecord(std::ifstream &ifs) {

    mLandTextures.resize(16);
    for (int x = 0; x < 16; x++) mLandTextures.at(x).resize(16);

    for (int y1 = 0; y1 < 4; y1++) {
        for (int x1 = 0; x1 < 4; x1++) {
            for (int y2 = 0; y2 < 4; y2++) {
                for (int x2 = 0; x2 < 4; x2++) {
                    ifs.read((char *) &mLandTextures[x1 * 4 + x2][y1 * 4 + y2], sizeof(uint16_t));
                }
            }
        }
    }
}

void ESLand::loadVhgtRecord(std::ifstream &ifs) {
    float offset;
    ifs.read((char *) &offset, sizeof(float));

    //mHeightData.resize(65);
    for (int i = 0; i < 65; i++) {
        mHeightData.at(i).resize(65);
        for (int j = 0; j < 65; j++) {
            mHeightData[i][j] = 0;
        }
    }

    for (int y = 0; y < 65; y++) {
        char x;
        ifs.get(x);
        offset += x;
        mHeightData.at(0).at(y) = +(int) offset;

        float pos = offset;

        for (int x = 1; x < 65; x++) {

            char c;
            int tmp = 0;
            ifs.get(c);
            pos += c;

            mHeightData.at(x).at(y) = (int) pos;

        }
    }

    char unk;
    ifs.read((char *) &unk, 1);


    uint16_t junk2 = 0;
    ifs.read((char *) &junk2, sizeof(uint16_t));
}

float ESLand::getHeightAt(float x, float y) {
    float cellX = _temp(x, 8192);
    float cellY = _temp(y, 8192);

    if (cellX < 0)cellX = 8192 + cellX;
    if (cellY < 0)cellY = 8192 + cellY;

    int posX = _temp2(cellX, 128) - 1;
    int posY = _temp2(cellY, 128) - 1;

    ////gets the offset from the vert of the object
    //float offsetX = _temp3(cellX);
    //float offsetY = _temp3(cellY);

    //float tri[3];

    //float nx1,ny1,nz1;

    //if ( offsetX < offsetY ){
    //	tri[0] = mHeightData[posX-1][posY-1];
    //	tri[1] = mHeightData[posX-1][posY];
    //	tri[2] = mHeightData[posX][posY];

    //	nx1 = (mLandNormal[posX][posY].x + mLandNormal[posX-1][posY-1].x + mLandNormal[posX-1][posY].x)/3;
    //	ny1 = (mLandNormal[posX][posY].y + mLandNormal[posX-1][posY-1].y + mLandNormal[posX-1][posY].y)/3;
    //	nz1 = (mLandNormal[posX][posY].z + mLandNormal[posX-1][posY-1].z + mLandNormal[posX-1][posY].z)/3;

    //}else{
    //	tri[0] = mHeightData[posX-1][posY-1];
    //	tri[1] = mHeightData[posX][posY-1];
    //	tri[2] = mHeightData[posX][posY];

    //	nx1 = (mLandNormal[posX][posY].x + mLandNormal[posX-1][posY-1].x + mLandNormal[posX][posY-1].x)/3;
    //	ny1 = (mLandNormal[posX][posY].y + mLandNormal[posX-1][posY-1].y + mLandNormal[posX][posY-1].y)/3;
    //	nz1 = (mLandNormal[posX][posY].z + mLandNormal[posX-1][posY-1].z + mLandNormal[posX][posY-1].z)/3;

    //}

    /////*float max = tri[0];
    ////max = std::min<float>(tri[1],max);
    ////max = std::min<float>(tri[2],max);*/

    //float z = tri[0]*8 + (nx1 * offsetX + ny1 * offsetY ) / float(offsetX + nz1);
    //////float z = max + (nx1 * offsetX + ny1 * offsetY ) / -nz1;
    //return z;//*8;

    //Equ
    //P.z = V0.z+ (N.x * dx + N.y * dy ) / -N.z

    //float a = mHeightData[posX-1][posY-1] - mHeightData[posX-1][posY];
    //float b = a / float(128) * offsetY;

    //float c = mHeightData[posX-1][posY-1] - mHeightData[posX][posY-1];
    //float d = c / float(128) * offsetX;

    //return (b + d + mHeightData[posX-1][posY-1])*8;

    /*
     start.x = _vertex( 0, 0, 0 );
    start.y = _vertex( 0, 0, 1 );
    start.z = _vertex( 0, 0, 2 );

    end.x = _vertex( mOptions->tileSize - 1, mOptions->tileSize - 1, 0 );
    end.y = _vertex( mOptions->tileSize - 1, mOptions->tileSize - 1, 1 );
    end.z = _vertex( mOptions->tileSize - 1, mOptions->tileSize - 1, 2 );
    */

    Vector3 end, start;

    start.z = mHeightData[0][0];


    end.x = 64 * 64;
    end.y = 64 * 64;
    end.z = mHeightData[64][64];

    //float x_pct = ( x - start.x ) / ( end.x - start.x );
    //float z_pct = ( z - start.z ) / ( end.z - start.z );

    float x_pct = (cellX - 0) / (8192);
    float z_pct = (cellY - 0) / (8192);

    float x_pt = x_pct * (float) (64);
    float z_pt = z_pct * (float) (64);

    int x_index = (int) (x_pt);
    int z_index = (int) (z_pt);
    //int x_index = posX;
    //int z_index = posY;

    // If we got to the far right / bottom edge, move one back
    if (x_index == 64) {
        --x_index;
        x_pct = 1.0f;
    } else {
        // get remainder
        x_pct = x_pt - x_index;
    }
    if (z_index == 64) {
        --z_index;
        z_pct = 1.0f;
    } else {
        z_pct = z_pt - z_index;
    }

    float t1 = mHeightData[x_index][z_index] * 8;
    float t2 = mHeightData[x_index + 1][z_index] * 8;
    float b1 = mHeightData[x_index][z_index + 1] * 8;
    float b2 = mHeightData[x_index + 1][z_index + 1] * 8;

    float midpoint = (b1 + t2) / 2.0;

    if (x_pct + z_pct <= 1) {
        b2 = midpoint + (midpoint - t1);
    } else {
        t1 = midpoint + (midpoint - b2);
    }

    float t = (t1 * (1 - x_pct)) + (t2 * (x_pct));
    float b = (b1 * (1 - x_pct)) + (b2 * (x_pct));

    float h = (t * (1 - z_pct)) + (b * (z_pct));

    return h + 16;

}

ES3::Vector3 ESLand::getAngleAt(float x, float y) {
    float cellX = _temp(x, 8192);
    float cellY = _temp(y, 8192);

    if (cellX < 0)cellX = 8192 + cellX;
    if (cellY < 0)cellY = 8192 + cellY;

    int posX = _temp2(cellX, 128);
    int posY = _temp2(cellY, 128);


    float v[4];
    v[0] = (float) mHeightData[posX][posY] * 8;
    v[1] = (float) mHeightData[posX - 1][posY] * 8;

    v[2] = (float) mHeightData[posX][posY - 1] * 8;
    v[3] = (float) mHeightData[posX - 1][posY - 1] * 8;
    ES3::Vector3 v3;
    v3.y = (atan((v[0] - v[1]) / 128) + atan((v[2] - v[3]) / 128)) / 2;


    v[0] = (float) mHeightData[posX][posY] * 8;
    v[1] = (float) mHeightData[posX][posY - 1] * 8;

    v[2] = (float) mHeightData[posX - 1][posY] * 8;
    v[3] = (float) mHeightData[posX - 1][posY - 1] * 8;
    v3.x = -(atan((v[0] - v[1]) / 128) + atan((v[2] - v[3]) / 128)) / 2;
    return v3;
}

void ESLand::read(std::ifstream &ifs, long recordSize) {
    std::streampos readTo = recordSize + ifs.tellg();

    while (ifs.tellg() < readTo) {
        char dataType[5];
        ifs.read(dataType, 4);

        //string must be null terminated.
        dataType[4] = '\0';
        uint32_t subRecSize;
        if (strcmp(dataType, "INTV") == 0) {
            ifs.read((char *) &subRecSize, sizeof(uint32_t));
            std::streampos recordStart = ifs.tellg();
            assert(sizeof(LandSquare) == 8);
            ifs.read((char *) &mLandSquare, sizeof(LandSquare));
            assert(ifs.tellg() == recordStart + std::streampos(subRecSize));
        } else if (strcmp(dataType, "VHGT") == 0) {
            ifs.read((char *) &subRecSize, sizeof(uint32_t));
            std::streampos recordStart = ifs.tellg();
            loadVhgtRecord(ifs);
            assert(ifs.tellg() == recordStart + std::streampos(subRecSize));
        } else if (strcmp(dataType, "VTEX") == 0) {
            ifs.read((char *) &subRecSize, sizeof(uint32_t));
            long recordStart = ifs.tellg();
            loadVtexRecord(ifs);
            assert(ifs.tellg() == recordStart + std::streampos(subRecSize));
        } else {
            handleUnknownRecord(ifs);
        }
    }
    ifs.seekg(readTo);
}

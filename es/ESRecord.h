#ifndef _ESRECORD_H_
#define _ESRECORD_H_

#include <string>
#include <vector>
#include <fstream>
#include <cassert>

#include "ESSubString.h"
#include "ESSubUnknown.h"

namespace ES3 {


/**
* Contains the data about a base record
*/
    class ESRecord {
    protected:
        /**
        * Used by inherited classes to deal with unknown records
        * @param &ifs ifstream positioned before the unknown record
        */
        void handelUnknownRecord(std::ifstream &ifs) {
            ESSubUnknown unk;
            unk.read(ifs);
        }

    public:

        /**
        * Read the subrecord
        * @param &ifs the pointer to the filestream
        * @param recordSize the size of the record to read
        */
        virtual void read(std::ifstream &ifs, long recordSize) = 0;


    };

}//namespace

#endif

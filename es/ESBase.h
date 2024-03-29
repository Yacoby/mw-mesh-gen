#ifndef _ESBASE_H_
#define _ESBASE_H_

#include <map>
#include "MapFunctions.h"


#include <vector>

#include "ESFile.h"


namespace ES3 {


    class ESFileContainer;

    typedef std::shared_ptr<ESFileContainer> ESFileContainerRef;


/**
* A helper class. Use it to load multiple files and then access data.
* It is advisable to always use this for mutliple files.
*/
    class ESFileContainer {
    protected:

        /**
        * Contains a list of the files. This is needed as some records canot be overwriten. (Cells for example),
        * so need to be stored on a per file basis.
        */
        std::vector<ESFileRef> mFile;
    public:
        bool loadDataFile(const std::string &file) {
            static std::map<std::string, ESFileRef> files;

            if (files.find(file) == files.end()) {
                files[file] = ESFileRef(new ESFile());
            }

            {
                if (files[file]->loadFile(file)) {
                    mFile.push_back(files[file]);
                    files.erase(file);

                    return true;
                }

                return false;

            }
            return true;
        }

        ESCellRef getFirstCell(int x, int y) {
            for (unsigned i = 0; i < mFile.size(); i++) {
                if (mFile[i]->cellExists(x, y)) {
                    return mFile[i]->getCell(x, y);
                }
            }
            return NULL;
        }

        /**
        *	Retuurns the land data for the selected grid
        *	@param squX The grid square x
        *	@param squY the grid square y
        */
        ESLandRef getLand(int squX, int squY) {
            for (unsigned i = 0; i < mFile.size(); i++) {
                if (mFile[i]->landExists(squX, squY)) {
                    return mFile[i]->getLand(squX, squY);
                }
            }
            return NULL;
        }

        ESFileRef getLandFile(int squX, int squY) {
            for (unsigned i = 0; i < mFile.size(); i++) {
                if (mFile[i]->landExists(squX, squY)) {
                    return mFile[i];
                }
            }
            return NULL;
        }

        std::set<std::pair<int32_t, int32_t >> getExteriorCellCoordinates() {
            std::set<std::pair<int32_t, int32_t> > result;
            for (unsigned i = 0; i < mFile.size(); i++) {
                const auto& coordinates = mFile[i]->getExteriorCellCoordinates();
                result.insert(coordinates.begin(), coordinates.end());
            }
            return result;
        }
    };

}//namespace

#endif

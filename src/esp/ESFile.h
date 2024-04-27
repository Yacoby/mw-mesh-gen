#ifndef _ESDATA_H_
#define _ESDATA_H_

#include <map>
#include <list>
#include <set>
#include <cstring>
#include <vector>
#include <filesystem>
#include <ostream>

#include "spdlog/fmt/fmt.h"

#include "ESCell.h"
#include "ESLand.h"
#include "ESLTex.h"

class GridId {
public:
    const int x;
    const int y;

    GridId(const int x, const int y);

    static GridId fromPosition(const double x, const double y);

    bool operator==(const GridId &rhs) const;
    bool operator!=(const GridId &rhs) const;
    bool operator<(const GridId &rhs) const;

    friend std::ostream& operator<<(std::ostream& os, const GridId& id);
};

template<>
struct fmt::formatter<GridId> {
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.end();
    }

    template <typename FormatContext>
    auto format(const GridId& input, FormatContext& ctx) -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "({}, {})", input.x, input.y);
    }
};

class ESFile;
typedef std::shared_ptr<ESFile> ESFileRef;

/**
* Holds the data for a single Morrowind file.
*/
class ESFile {
private:
    std::filesystem::path filePath;
    /**
    * A list of exterior cells, listed by grid
    */
    std::map<GridId, ESCellRef> mpExteriorCell;

    std::map<GridId, ESLandRef> mpLand;

    std::map<long, ESLTexRef> mLandTex;
    std::vector<ESLTexRef> mLandTexVec;
public:

    const std::filesystem::path& getFilePath() {
        return filePath;
    }

    void loadFile(const std::filesystem::path &pFile);

    ESLTexRef getLTex(long id) const {
        return mLandTexVec.at(id);
    }

    ESCellRef getCell(int squX, int squY) {
        ESCellRef ref = mpExteriorCell[GridId(squX, squY)];
        return ref;
    }

    ESLandRef getLand(int squX, int squY) {
        ESLandRef ref = mpLand[GridId(squX, squY)];
        return ref;
    }

    bool landExists(const int squX, const int squY) const {
        return mpLand.find(GridId(squX, squY)) != mpLand.end();
    }

    bool getLTexExists(int index) const {
        return mLandTex.find(index) != mLandTex.end();
    }

    const std::string& getLTexPath(int index) {
        return mLandTex[index]->getPath();
    }

    std::set<std::pair<int32_t, int32_t >> getExteriorCellCoordinates() {
        std::set<std::pair<int32_t, int32_t> > result;
        for (const auto &xCordAndCells: mpLand) {
            result.insert(std::pair(xCordAndCells.first.x, xCordAndCells.first.y));
        }
        return result;
    }
};

#endif

#include "ESLTex.h"

ESLTex ESLTex::load(EspReader::Record& record) {
    ESLTex ltex;

    for (auto &subRecord: record) {
        if (subRecord.type == "NAME") {
            ltex.mName = subRecord.readNullTerminatedString();
        } else if (subRecord.type == "INTV") {
            ltex.mIndex = subRecord.read<uint32_t>();
        } else if (subRecord.type == "DATA") {
            ltex.mPath = subRecord.readNullTerminatedString();
        }
    }

    return ltex;
}

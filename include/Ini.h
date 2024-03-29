#ifndef __INI_H_
#define __INI_H_

#include <boost/algorithm/string.hpp>
#include <optional>

class Ini {

protected:
    typedef std::map<std::string, std::map<std::string, std::string> > IniValues;
    typedef std::map<std::string, std::map<std::string, std::string> >::iterator IniValuesItr;
    IniValues mValues;
public:

    bool catExists(const std::string &cat) {
        return mValues.find(cat) != mValues.end();
    }

    bool valueExists(const std::string &cat, const std::string &key) {
        auto categoryLookup = mValues.find(cat);
        if (categoryLookup == mValues.end()) {
            return false;
        }
        return categoryLookup->second.find(key) != categoryLookup->second.end();
    }

    std::optional<const std::reference_wrapper<std::string>> getOptionalValue(const std::string &cat, const std::string &key) {
        auto categoryLookup = mValues.find(cat);
        if (categoryLookup == mValues.end()) {
            return std::nullopt;
        }
        auto keyLookup = categoryLookup->second.find(key);
        if (keyLookup == categoryLookup->second.end()) {
            return std::nullopt;
        }
        return keyLookup->second;
    }

    const std::string& getValue(const std::string &cat, const std::string &key) {
        auto categoryLookup = mValues.find(cat);

        if (categoryLookup == mValues.end()) {
            std::string msg = "When getting ini category, the category doesn't exist\nExpecting category \"" + cat +
                              "\" to exist. (Was looking for the key \"" + key + "\")";
            throw std::invalid_argument(msg);
        }

        auto valueLookup = categoryLookup->second.find(key);
        if (valueLookup == categoryLookup->second.end()) {
            std::string msg = "When getting ini value, value doesn't exist\nExpecting category \"" + cat +
                              "\" to contain key \"" + key + "\"";
            throw std::invalid_argument(msg);
        }

        return valueLookup->second;
    }

    bool load(const std::string &f) {
        std::string curBlok;

        std::ifstream ifs(f.c_str());
        if (!ifs.is_open()) return false;


        std::string line, key, val;
        while (!ifs.eof()) {
            std::getline(ifs, line);

            int commentIdx = line.find(";");
            if (commentIdx != -1) {
                line = line.substr(0, commentIdx);
            }

            boost::trim(line);
            boost::trim_right_if(line, boost::is_any_of("\r\n\0"));

            if (line.find("[") == 0 && line.rfind("]") != -1) {
                curBlok = line.substr(1, line.rfind("]") - 1);
                continue;
            }


            size_t pos = line.find("=");
            if (pos == -1) continue; //not a valid value

            key = line.substr(0, pos);
            val = line.substr(pos + 1, line.length() - pos + 1);

            mValues[curBlok][key] = val;
        }
        ifs.close();
        return true;
    }
};

class GrassIni2 : public Ini {
public:
    struct GrassMesh {
        std::string mesh;
        std::string objectID;
        float chance;
        int id;
    };
public:

    /**
    * gets a list of all the texutes used
    */
    std::list<std::string> getTextureList() {
        std::list<std::string> lst;
        for (IniValuesItr iter = mValues.begin(); iter != mValues.end(); ++iter) {
            lst.push_back(iter->first);
        }
        return lst;
    }

    /**
    * @brief gets a list of meshes used by a texture
    */
    std::list<GrassMesh> getMeshList(const std::string &cat) {
        std::list<GrassMesh> lst;
        for (int c = 0; ; ++c) {
            const std::string &stringIdx = toString(c);
            auto mesh = getOptionalValue(cat, "sMesh" + stringIdx);
            if (!mesh.has_value()) {
                break;
            }

            GrassMesh g;
            g.mesh = mesh.value();
            g.chance = fromString<float>(getValue(cat, "sChance" + stringIdx));

            auto id = getOptionalValue(cat, "sID" + stringIdx);
            if (id.has_value()) {
                g.objectID = id.value();
            }
            g.id = c;
            lst.push_back(g);
        }
        return lst;
    }
};

#endif //__INI_H_

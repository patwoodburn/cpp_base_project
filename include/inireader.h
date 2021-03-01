// conan does not bring in cpp inpul of inih
#pragma once

#include <map>
#include <string>

#include "ini.h"
#include "inputparser.h"

class INIReader {
    private:
        int error;
        std::map<std::string, std::string> values;

        static std::string MakeKey(const std::string& section, const std::string& name) {
            std::string key = section + "=" + name;
            // Convert to lower case to make section/name lookups case-insensitive
            std::transform(key.begin(), key.end(), key.begin(), ::tolower);
            return key;
        }

        static int ValueHandler(void* user, const char* section, const char* name, const char* value) {
            if (!name) {
                return 1;
            }
            INIReader* reader = static_cast<INIReader*>(user);
            std::string key = MakeKey(section, name);
            if (reader->values[key].size() > 0) {
                reader->values[key] += "\n";
            }
            reader->values[key] += value ? value : "";
            return 1;
        }
        
    public:
        explicit INIReader(const std::string& filename){
            error = ini_parse(filename.c_str(), ValueHandler, this);
        }

        int ParseErorr(){ return error; }

        std::string Get(const std::string& section, const std::string& name, const std::string& default_value) const {
            std::string key = MakeKey(section, name);
            return values.count(key) ? values.find(key)->second : default_value;
        }

        std::string GetString(const std::string& section, const std::string& name, const std::string& default_value) const {
            const std::string str = Get(section, name, "");
            return str.empty() ? default_value : str;
        }


};

INIReader& getApplicationConfig() {
    static INIReader config = INIReader(
        InputParser::getInstance().cmdOptionExists("-f") ?
        std::string{InputParser::getInstance().getCmdOption("-f")} :
        "/etec/cpp_base_project/config"
    );
    return config;
}
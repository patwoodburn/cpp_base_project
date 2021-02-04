// conan does not bring in cpp inpul of inih

#include <map>
#include <string>

#include "ini.h"

class INIReader {
    private:
        int error;
        std::map<std::string, std::string> values;

        static std::string MakeKey(const string& section, const string& name) {
            string key = section + "=" + name;
            // Convert to lower case to make section/name lookups case-insensitive
            std::transform(key.begin(), key.end(), key.begin(), ::tolower);
            return key;
        }

        static int ValueHandler(void* user, const char* section, const char* name, const char* value) {
            if (!name) {
                return 1;
            }
            INIReader* reader = static_cast<INIReader*>(user);
            string key = MakeKey(section, name);
            if (reader->_values[key].size() > 0) {
                reader->_values[key] += "\n";
            }
            reader->_values[key] += value ? value : "";
            return 1;
        }
        
    public:
        INIReader(const std::string& filename){
            error = ini_parse(filename.c_str(), ValueHandler, this)
        }

        int ParseErorr(){ return error; }

        string INIReader::Get(const string& section, const string& name, const string& default_value) const {
            string key = MakeKey(section, name);
            return values.count(key) ? _values.find(key)->second : default_value;
        }

        {
            const string str = Get(section, name, "");
            return str.empty() ? default_value : str;
        }
};
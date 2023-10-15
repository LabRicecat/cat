#ifndef CAT_CONFIG_HPP
#define CAT_CONFIG_HPP

#include <filesystem>
#include <string>
#include <fstream>

// ncurses workaround 
#ifdef OK 
# undef OK
#endif
#include "catpkgs/inipp/inipp.hpp" 
#ifndef OK 
# define OK (1)
#endif 

#include "signals.hpp"

namespace cat {

namespace config {
    namespace fs = std::filesystem;
    inline bool opened = false;
    inline fs::path config_file;
    inline IniFile config_mirror;

    inline std::string config_defaults = "";

    inline signals::signal config_error = signals::create(signals::error_tag);

    void at(const fs::path& path);
    void sync();

    /* not adviced to use */ 
    void apply();
    bool has(const std::string& key, const std::string& section = "Main");

    /* adviced to use get_or instead */
    template<typename T = IniElement>
    inline T get(const std::string& key, const std::string& section = "Main") {
        return (T)config_mirror.get(key,section);
    }

    template<typename T = IniElement>
    inline T get_or(const std::string& key, const std::string& section, const T& g_or) {
        if(config_mirror.has(key,section)) 
            return (T)config_mirror.get(key,section);

        return g_or;
    }

    std::string& add_default(const std::string& adefault);
    void write_default();

    template<IniType type = IniType::Null>
    inline void ensure(const std::string& key, const std::string& section = "Main", const IniElement& value = IniElement()) {
            if(!has(key,section)) {
                signals::emit(config_error, new signals::MessageData("key " + key + " in section " + section + " does not exist!"));
                return;
            }

            IniElement elem = get(key,section);
            if(type != IniType::Null && elem.get_type() != type) {
                signals::emit(config_error, new signals::MessageData("key " + key + " in section " + section + " is not of type " + IniType2str(value.get_type()) + " (it's of type " + IniType2str(elem.get_type()) + ")"));
                return;
            }

            if(value.get_type() != IniType::Null && value.to_string() != elem.to_string()) {
                signals::emit(config_error, new signals::MessageData("key " + key + " in section " + section + " is not of value " + value.to_string() + " (it's of value " + elem.to_string() + ")"));
            }
    }
} // namespace config

} // namespace cat 

#endif


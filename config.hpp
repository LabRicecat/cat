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
    static inline bool opened = false;
    static inline fs::path config_file;
    static inline IniFile config_mirror;

    static inline std::string config_defaults = "";
    static inline std::string config_cat_default = 
R"([CAT_TUI]
frame_sleep = 75
)"; 

    static inline signals::signal config_error = signals::create(signals::error_tag);

    static inline void at(const fs::path& path) {
        config_file = path;
    }

    static inline void sync() {
        if(config_file == "") return;
        opened = true;
        config_mirror = IniFile::from_file(config_file.string());
    }

    /* not adviced to use */ 
    static inline void apply() {
        if(config_file == "") return;
        config_mirror.to_file(config_file.string()); 
    }

    static inline bool has(const std::string& key, const std::string& section = "Main") {
        return config_mirror.has(key, section);    
    }

    /* adviced to use get_or instead */
    template<typename T = IniElement>
    static inline T get(const std::string& key, const std::string& section = "Main") {
        return (T)config_mirror.get(key,section);
    }

    template<typename T = IniElement>
    static inline T get_or(const std::string& key, const std::string& section, const T& g_or) {
        if(config_mirror.has(key,section)) 
            return (T)config_mirror.get(key,section);

        return g_or;
    }

    static inline std::string& add_default(const std::string& adefault) {
        return config_defaults += adefault;
    }

    static inline void write_default() { // TODO: permission problems may occur
        if(!fs::exists(config_file))
            fs::create_directories(config_file.parent_path());
        
        std::ofstream o;
        o.open(config_file.string(), std::ios::trunc);
        o.close();
        
        o.open(config_file.string());
        o << config_cat_default << config_defaults;
        o.close();
    }

    template<IniType type = IniType::Null>
    static inline void ensure(const std::string& key, const std::string& section = "Main", const IniElement& value = IniElement()) {
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
}

}

#endif


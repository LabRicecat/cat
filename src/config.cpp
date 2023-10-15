#include "../inc/config.hpp"

namespace cat {

namespace config {

void at(const fs::path& path) {
    config_file = path;
}

void sync() {
    if(config_file == "") return;
    opened = true;
    config_mirror = IniFile::from_file(config_file.string());
 }

/* not adviced to use */ 
void apply() {
    if(config_file == "") return;
    config_mirror.to_file(config_file.string()); 
}

bool has(const std::string& key, const std::string& section) {
    return config_mirror.has(key, section);    
}

std::string& add_default(const std::string& adefault) {
    return config_defaults += adefault;
}

void write_default() { // TODO: permission problems may occur
    if(!fs::exists(config_file))
        fs::create_directories(config_file.parent_path());
        
    std::ofstream o;
    o.open(config_file.string(), std::ios::trunc);
    o.close();
        
    o.open(config_file.string());
    o << config_defaults;
    o.close();
}

} // namespace config 

} // namespace cat

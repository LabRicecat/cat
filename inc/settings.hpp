#ifndef CAT_SETTINGS_HPP
#define CAT_SETTINGS_HPP

#include <string>
#include <cstdint>

namespace cat {

struct Settings {
    uint64_t tick_sleep = 25; // miliseconds
    bool color = true;
};

inline Settings current_settings;

Settings apply(const Settings& applied);

} // namespace cat

#endif

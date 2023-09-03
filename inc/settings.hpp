#ifndef CAT_SETTINGS_HPP
#define CAT_SETTINGS_HPP

#include <string>
#include <cstdint>

namespace cat {

struct Settings {
    uint64_t tick_sleep = 25; // In miliseconds
    bool color = true;        // Enable color mode
    bool stuck_cursor = true; // Move the cursor back to it's original position
                              // after a redraw
};

inline Settings current_settings;

Settings apply(const Settings& applied);

} // namespace cat

#endif

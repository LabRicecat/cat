#ifndef CAT_INPUT_HPP
#define CAT_INPUT_HPP

#include <ncurses.h>
#include <functional>
#include <map>

namespace cat {

using key = int;
using key_event = std::function<void()>;
using keymap = std::map<key,key_event>;

inline static keymap global_keymap = {};

inline static void set_keymap(const key& skey, const key_event& event) {
    global_keymap[skey] = event;
}

inline static bool in_global_keymap(const key& skey) {
    return global_keymap.find(skey) != global_keymap.end();
}

}

#endif

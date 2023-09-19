#include "../../inc/base/input.hpp"

namespace cat {

void set_keymap(const key& skey, const key_event& event) {
    global_keymap[skey] = event;
}

void set_keymap(std::map<const key, const key_event> maps) {
    global_keymap.insert(maps.begin(), maps.end());
}

bool in_global_keymap(const key& skey) {
    return global_keymap.find(skey) != global_keymap.end();
}

key shift(const key& k) { return k & 0x1f; }

} // namespace cat

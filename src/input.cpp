#include "../inc/input.hpp"

namespace cat {

void set_keymap(const key& skey, const key_event& event) {
    global_keymap[skey] = event;
}

bool in_global_keymap(const key& skey) {
    return global_keymap.find(skey) != global_keymap.end();
}

key shift(const key& k) { return k & 0x1f; }

} // namespace cat

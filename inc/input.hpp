#ifndef CAT_INPUT_HPP
#define CAT_INPUT_HPP

#include <ncurses.h>
#include <functional>
#include <map>

namespace cat {

using key = int;
using key_event = std::function<void()>;
using keymap = std::map<key,key_event>;

inline keymap global_keymap = {};

void set_keymap(const key& skey, const key_event& event);
void set_keymap(std::map<const key, const key_event> events);

bool in_global_keymap(const key& skey);

key shift(const key& k); 

} // namespace cat

#endif

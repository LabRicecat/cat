#ifndef CAT_DRAWCALLS_HPP
#define CAT_DRAWCALLS_HPP

#include <stdarg.h>
#include <ncurses.h>
#include <functional>

#include "string.hpp"
#include "vector.hpp"

namespace cat {

class Window;

using draw_behaviour = std::function<void(WINDOW*, size_t, const char*)>;

void draw_base(Window* win, const CatString& fmstr, const draw_behaviour& draw, bool do_cformat, size_t argsize, ...); 

template<typename... Targs>
static inline void draw(Window* win, const CatString& fmstr, Targs... args) {
    const size_t pack_size = sizeof...(args);
    draw_base(win, fmstr, [](WINDOW* w, size_t s, const char* c) { wprintw(w,"%s",c); }, true, pack_size, args...);
}

template<typename... Targs>
static inline void draw(const Vector2& position, Window* win, const CatString& fmstr, Targs... args) {
    const size_t pack_size = sizeof...(args);
    draw_base(win, fmstr, [&](WINDOW* w, size_t s, const char* c) { mvwprintw(w, position.y, position.x,"%s",c); }, true, pack_size, args...);
}

} // namespace cat

#endif 

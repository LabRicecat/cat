#ifndef CAT_DRAWCALLS_HPP
#define CAT_DRAWCALLS_HPP

#include <stdarg.h>
#include <ncurses.h>
#include <functional>

#include "string.hpp"
#include "vector.hpp"

namespace cat {

using draw_behaviour = std::function<void(WINDOW*, size_t, const char*)>;

inline void draw_base(WINDOW* win, const CatString& fmstr, const draw_behaviour& draw, bool do_cformat, size_t argsize, ...) {
    CatString fmstrc = fmstr;
    va_list arglist;
    va_start(arglist, argsize);

    for(auto& i : fmstrc.entries()) {
        if(i.str) {
            if(!do_cformat) { 
                draw(win, i.s.size(), i.s.c_str());
                continue;
            }
            va_list cpylist;
            va_copy(cpylist, arglist);

            size_t buf_size = vsnprintf(NULL, 0, i.s.c_str(), cpylist) + 1;
            char buf[buf_size];
            vsnprintf(buf, buf_size, i.s.c_str(), arglist);

            draw(win, buf_size, buf);
        }
        else i.fn(fmstrc, win);
    }

    wattron(win, A_NORMAL);
    attron(A_NORMAL);
    wattrset(win, A_NORMAL);
    attrset(A_NORMAL);
}  

template<typename... Targs>
inline void draw(WINDOW* win, const CatString& fmstr, Targs... args) {
    const size_t pack_size = sizeof...(args);
    draw_base(win, fmstr, [](WINDOW* w, size_t s, const char* c) { wprintw(w,"%s",c); }, true, pack_size, args...);
}

template<typename... Targs>
inline void draw(const Vector2& position, WINDOW* win, const CatString& fmstr, Targs... args) {
    const size_t pack_size = sizeof...(args);
    draw_base(win, fmstr, [&](WINDOW* w, size_t s, const char* c) { mvwprintw(w, position.y, position.x,"%s",c); }, true, pack_size, args...);
}

} // namespace cat

#endif 

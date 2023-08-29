#include "../inc/drawcalls.hpp"
#include "../inc/window.hpp"

namespace cat {

void draw_base(Window* winn, const CatString& fmstr, const draw_behaviour& draw, bool do_cformat, size_t argsize, ...) {
    CatString fmstrc = fmstr;
    va_list arglist;
    va_start(arglist, argsize);

    WINDOW* win = winn->ncurses_window;

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

} // namespace cat

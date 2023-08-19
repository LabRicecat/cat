#ifndef CAT_TERMINAL_HPP
#define CAT_TERMINAL_HPP

#include <ncurses.h>

namespace cat {

namespace terminal { // TODO: expand with more terminal specific data/configurations 
    static inline int get_x() { return getmaxx(stdscr); }
    static inline int get_y() { return getmaxy(stdscr); }
}

}

#endif

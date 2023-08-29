#ifndef CAT_TERMINAL_HPP
#define CAT_TERMINAL_HPP

#include <ncurses.h>

namespace cat {

namespace terminal { // TODO: expand with more terminal specific data/configurations 
    // return the max resolution of the screen 
    int get_x();
    int get_y();
} // namespace terminal 

} // namespace cat 

#endif

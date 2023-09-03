#ifndef CAT_TERMINAL_HPP
#define CAT_TERMINAL_HPP

#include <ncurses.h>

#include "vector.hpp"

namespace cat {

namespace terminal { // TODO: expand with more terminal specific data/configurations 
    // return the max resolution of the screen 
    Vector2::value_type get_x();
    Vector2::value_type get_y();
} // namespace terminal 

} // namespace cat 

#endif

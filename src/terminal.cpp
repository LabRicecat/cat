#include "../inc/terminal.hpp"

namespace cat {

namespace terminal {

Vector2::value_type get_x() { return (Vector2::value_type)getmaxx(stdscr); }
Vector2::value_type get_y() { return (Vector2::value_type)getmaxy(stdscr); }

}

}

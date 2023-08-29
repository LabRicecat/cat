#include "../inc/terminal.hpp"

namespace cat {

namespace terminal {

int get_x() { return getmaxx(stdscr); }
int get_y() { return getmaxy(stdscr); }

}

}

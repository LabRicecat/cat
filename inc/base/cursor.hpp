#ifndef CAT_CURSOR_HPP
#define CAT_CURSOR_HPP

#include <ncurses.h>

#include "vector.hpp"

namespace cat {

class Window;

struct curs_position {
    WINDOW* win = nullptr;
    Vector2 position;
};

inline curs_position cursor { stdscr, {0,0} };

curs_position get_cursor();

void move_cursor_global(const Vector2& position);
void move_cursor(Window* win, const Vector2& position);
void move_cursor(const curs_position& position);
void move_cursor_relative(const Vector2& movement);

}

#endif 

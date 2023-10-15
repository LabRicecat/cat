#include "../inc/cursor.hpp"
#include "../inc/window.hpp"

namespace cat {

curs_position get_cursor() {
    cursor.position = Vector2{ getcurx(cursor.win), getcury(cursor.win) };
    return cursor;
}

void move_cursor_global(const Vector2& position) {
    wmove(stdscr, position.y, position.y);
    cursor.win = stdscr;
    cursor.position = position;
}
void move_cursor(Window* win, const Vector2& position) {
    wmove(win->ncurses_window, position.y, position.x);
    cursor.win = win->ncurses_window;
    cursor.position = position;
}

void move_cursor(const curs_position& pos) {
    cursor = pos;
    wmove(cursor.win, cursor.position.y, cursor.position.x);
}

void move_cursor_relative(const Vector2& movement) {
    cursor.position += movement;
}

} // namespace cat

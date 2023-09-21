#include "../../inc/base/window.hpp"

namespace cat {

const id_type& Window::get_id() {
    return id;
}

Window& Window::clear() {
    wclear(ncurses_window);
    return *this;
}

Window& Window::redraw() {
    redraw_request = true;
    return *this;
}

Window& Window::move(const Vector2& position) {
    Positional::move(position);
    mvwin(ncurses_window, position.y, position.x);
    return *this;
}

Window& Window::resize(const Vector2& resolution) {
    Positional::resize(resolution);
    wresize(ncurses_window, resolution.y, resolution.x);
    return *this;
}

Window& Window::box(int chtype) {
    ::box(ncurses_window,chtype,chtype); 
    return *this;
}

Window& Window::background(const effect::color& color) {
    wbkgd(ncurses_window, COLOR_PAIR(color));
    return *this;
}

Window& Window::cursor(const Vector2& position, bool absolute) {
    if(absolute)
        cat::move_cursor_global(position);
    else
        cat::move_cursor(this, get_position() + position);
    return *this;
}

Window Window::duplicate() {
    Window w = *this;
    w.ncurses_window = dupwin(ncurses_window);
    return w;
}

Window& Window::adopt(Window* win) {
    syncs.push_back(win);
    return *this;
}

Window& Window::sync() {
    /* to implement by derived classes */
    return *this;
}
    
Window& Window::trigger_syncs() {
    for(auto& i : syncs)
            i->sync();
    return *this;
}

Window& Window::hide(bool status) {
    is_hidden = status;
    return *this;
}

Window& Window::unhide() { return hide(false); }

bool Window::hidden() { return is_hidden; }

Window& Window::focus(bool status) {
    is_focused = status;

    for(auto& i : focus_events)
        i(this,status);

    return *this;
}

Window& Window::lose_focus() { return focus(false); }

bool Window::focused() { return is_focused; }

Window& Window::set_key(const key& skey, const key_event& event) {
    win_keymap[skey] = event;
    return *this;
}

Window& Window::unset_key(const key& skey) {
    win_keymap.erase(skey);
    return *this;
}

Window& Window::set_key_handler(const key_checker_type& check, const key_handler_type& handler) {
    key_handler = handler;
    key_check = check;
    return *this;
}

const Window::key_handler_type& Window::get_key_handler() {
    return key_handler;
}

const Window::key_checker_type& Window::get_key_check() {
    return key_check;
}

bool Window::do_key_check(const key& skey) {
    if(!key_check) return false;
    return key_check(skey);
}

bool Window::has_key(const key& skey) {
    return win_keymap.find(skey) != win_keymap.end(); 
}

key_event& Window::get_key_event(const key& skey) {
    return win_keymap[skey];
}

Window& Window::draw_buffer() {
    if(!buffer) return *this;
    this->move({0,0});
    draw_base(ncurses_window, buffer->display(), [&](WINDOW* w,size_t s,const char* c) { wprintw(w, "%s", c); }, false, 0); 
    return *this;
}

Window& Window::on_redraw(const redraw_event& event) {
    redraw_events.push_back(event);
    return *this;
}

Window& Window::on_focus(const focus_event& event) {
    focus_events.push_back(event);
    return *this;
}
    
} // namespace cat 

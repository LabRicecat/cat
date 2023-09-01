#include "../inc/window.hpp"

namespace cat {

const id_type& Window::get_id() {
    return id;
}

const Vector2& Window::get_resolution() {
    return resolution;
}

const Vector2& Window::get_position() {
    return position;
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
    mvwin(ncurses_window, position.y, position.x);
    this->position = position;
    return *this;
}

Window& Window::resize(const Vector2& resolution) {
    wresize(ncurses_window, resolution.y, resolution.x);
    this->resolution = resolution;
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
        ::move(position.y, position.x);
    else
        ::wmove(ncurses_window, position.y, position.x);
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

Window& Window::draw_buffer(const Vector2& offset) {
    if(!buffer) return *this;

    auto display = buffer->display();
    draw_base(ncurses_window, buffer->display(), [&](WINDOW* w,size_t s,const char* c) { mvwprintw(w, position.y, position.x, "%s", c); }, false, 0); 
    return *this;
}

Window& Window::on_redraw(const redraw_event& event) {
    redraw_events.push_back(event);
    return *this;
}

    
} // namespace cat 

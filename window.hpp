#ifndef CAT_WINDOW_HPP
#define CAT_WINDOW_HPP

#include <ncurses.h>
#include <string>
#include <vector>

#include "vector.hpp"
#include "input.hpp"
#include "id.hpp"
#include "buffer.hpp" 

namespace cat {

static inline void redraw();

class Window {
protected:
    WINDOW* ncurses_window = nullptr;
    Vector2 position;
    Vector2 resolution;

    bool redraw_request = false;
    std::vector<Window*> syncs;

    bool is_focused = false;
    bool is_hidden = false;

    using key_checker_type = std::function<bool(const key&)>;
    using key_handler_type = std::function<void(const key&)>;
    keymap win_keymap;
    key_handler_type key_handler;
    key_checker_type key_check;

    id_type id;

    Buffer* buffer = nullptr;
public:

    Window() = delete;
    Window(const Vector2& position, const Vector2& resolution)
    : position(position), resolution(resolution) {
        ncurses_window = newwin(resolution.y,  resolution.x, position.y, position.x);
        id = new_id();
    }

    virtual ~Window() {
        if(ncurses_window)
            delwin(ncurses_window);
    }
   
    virtual const id_type& get_id() {
        return id;
    }

    virtual Window& clear() {
        wclear(ncurses_window);
        return *this;
    }

    virtual Window& redraw() {
        redraw_request = true;
        return *this;
    }

    virtual Window& move(const Vector2& position) {
        mvwin(ncurses_window, position.y, position.x);
        this->position = position;
        return *this;
    }

    virtual Window& resize(const Vector2& resolution) {
        wresize(ncurses_window, resolution.y, resolution.x);
        this->resolution = resolution;
        return *this;
    }

    virtual Window& box(int chtype = 0) {
        ::box(ncurses_window,chtype,chtype); 
        return *this;
    }

    virtual Window duplicate() {
        Window w = *this;
        w.ncurses_window = dupwin(ncurses_window);
        return w;
    }

    virtual Window& adopt(Window& win) {
        syncs.push_back(&win);
        return *this;
    }

    virtual Window& sync() {
        /* to implement by derived classes */
        return *this;
    }
    
    virtual Window& trigger_syncs() {
        for(auto& i : syncs)
                i->sync();
        return *this;
    }

    virtual Window& hide(bool status = true) {
        is_hidden = status;
        return *this;
    }

    virtual Window& unhide() { return hide(false); }

    virtual bool hidden() { return is_hidden; }

    virtual Window& focus(bool status = true) {
        is_focused = status;
        return *this;
    }

    virtual Window& lose_focus() { return focus(false); }

    virtual bool focused() { return is_focused; }

    virtual Window& set_buffer(Buffer* buffer) {
        this->buffer = buffer;
        return *this;
    }

    virtual Buffer* get_buffer() {
        return buffer;
    }

    virtual Window& set_key(const key& skey, const key_event& event) {
        win_keymap[skey] = event;
        return *this;
    }

    virtual Window& unset_key(const key& skey) {
        win_keymap.erase(skey);
        return *this;
    }

    virtual Window& set_key_handler(const key_checker_type& check, const key_handler_type& handler) {
        key_handler = handler;
        key_check = check;
        return *this;
    }

    virtual const key_handler_type& get_key_handler() {
        return key_handler;
    }
    virtual const key_checker_type& get_key_check() {
        return key_check;
    }
    virtual bool do_key_check(const key& skey) {
        if(!key_check) return false;
        return key_check(skey);
    }

    virtual bool has_key(const key& skey) {
        return win_keymap.find(skey) != win_keymap.end(); 
    }

    virtual key_event& get_key_event(const key& skey) {
        return win_keymap[skey];
    }

    virtual void start() {
        // left for derived implementation 
    }

    virtual void end() {
        // left for derived implementation
    }

    template<typename ...Tfargs>
    Window& draw_at(const Vector2& position, const std::string& fmstr, const Tfargs&... fargs) {
        mvwprintw(ncurses_window, position.y, position.x, fmstr.c_str(), fargs...);
        return *this;
    }

    template<typename ...Tfargs>
    Window& draw(const std::string& fmstr, const Tfargs&... fargs) {
        wprintw(ncurses_window, fmstr.c_str(), fargs...);
        return *this;
    }

    virtual Window& draw_buffer(const Vector2& offset = {0,0}) {
        if(!buffer) return *this;

        auto display = buffer->display();
        return draw_at(offset, "%s", display.c_str());
    }

    friend void redraw();
};

}

#endif

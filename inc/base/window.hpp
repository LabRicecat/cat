#ifndef CAT_WINDOW_HPP
#define CAT_WINDOW_HPP

#include <ncurses.h>
#include <string>
#include <vector>
#include <set>

#include "vector.hpp"
#include "input.hpp"
#include "id.hpp"
#include "buffer.hpp"
#include "drawcalls.hpp"
#include "effects.hpp"
#include "positional.hpp"
#include "cursor.hpp"

namespace cat {

extern void redraw();
 
class Window : public Positional {
public:
    using redraw_event = std::function<void(Window*)>;
    using focus_event = std::function<void(Window*,bool)>;
protected:
    WINDOW* ncurses_window = nullptr;

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

    std::vector<redraw_event> redraw_events;
    std::vector<focus_event> focus_events;
public:

    Window() = delete;
    Window(const Vector2& position, const Vector2& resolution)
    : Positional(position, resolution) {
        ncurses_window = newwin(resolution.y,  resolution.x, position.y, position.x);
        id = new_id();
    }

    virtual ~Window() {
        if(ncurses_window)
            delwin(ncurses_window);
        if(buffer)
            delete buffer;
    }
   
    virtual const id_type& get_id();

    virtual Window& clear();
    virtual Window& redraw();
    virtual Window& move(const Vector2& position) override;
    virtual Window& resize(const Vector2& resolution) override;
    virtual Window& box(int chtype = 0);
    virtual Window& background(const effect::color& color);
    virtual Window& cursor(const Vector2& position, bool absolute = false);
    virtual Window duplicate();

    virtual Window& adopt(Window* win);
    virtual Window& sync();
    virtual Window& trigger_syncs();

    virtual Window& hide(bool status = true);
    virtual Window& unhide();
    virtual bool hidden();

    virtual Window& focus(bool status = true);
    virtual Window& lose_focus();
    virtual bool focused();

    template<typename TBuffer = Buffer>
        requires ( std::is_base_of_v<Buffer,TBuffer> )
    inline Window& set_buffer(Renderer renderer = Renderer::null, Composer composer = Composer::null) {
        if(buffer)
            delete buffer;
        buffer = new TBuffer(this);
        buffer->composer() &= composer;
        buffer->renderer() &= renderer;
        return *this;
    }

    template<typename TBuffer = Buffer>
        requires ( std::is_base_of_v<Buffer,TBuffer> )
    inline TBuffer* get_buffer() {
        return dynamic_cast<TBuffer*>(buffer);
    }
 
    virtual Window& set_key(const key& skey, const key_event& event);
    virtual Window& unset_key(const key& skey);
    virtual Window& set_key_handler(const key_checker_type& check, const key_handler_type& handler); 
    virtual const key_handler_type& get_key_handler();
    virtual const key_checker_type& get_key_check();
    virtual bool do_key_check(const key& skey);
    virtual bool has_key(const key& skey);
    virtual key_event& get_key_event(const key& skey);

    template<typename ...Tfargs>
    inline Window& draw_at(const Vector2& position, const CatString& fmstr, const Tfargs&... fargs) {
        cat::draw(position, ncurses_window, fmstr, fargs...);
        return *this;
    }

    template<typename ...Tfargs>
    inline Window& draw(const CatString& fmstr, const Tfargs&... fargs) {
        cat::draw(ncurses_window, fmstr, fargs...);
        return *this;
    }

    virtual Window& draw_buffer();

    virtual Window& on_redraw(const redraw_event& event);
    virtual Window& on_focus(const focus_event& event);

    template<typename TWindow>
        requires ( std::is_base_of_v<Window,TWindow> )
    inline bool viable_as() const {
        return !!dynamic_cast<const TWindow*>(this);
    }
    
    friend void redraw();
    friend void move_cursor(Window*, const Vector2&);
};

}

#endif

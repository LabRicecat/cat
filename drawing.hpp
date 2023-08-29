#ifndef CAT_DRAWING_HPP
#define CAT_DRAWING_HPP

#include <ncurses.h>
#include <vector>
#include <vector>

#include "window.hpp" 
#include "effects.hpp"

namespace cat {

static inline std::vector<Window*> window_pool;

/* it's adviced not to call this function frequently, 
   and let Lifespan.hpp manage it */
inline static void redraw() {
    for(auto& i : window_pool)
        if(i && !i->hidden() && i->redraw_request) {
            for(auto& event : i->redraw_events)
                event(i);

            wrefresh(i->ncurses_window);
            i->redraw_request = false;
            i->trigger_syncs();
        }
}

template<typename TWindow = Window>
    requires ( std::is_base_of_v<Window,TWindow> )
static inline TWindow* new_window(TWindow* win) {
    window_pool.push_back((Window*)win);
    return win;
}

template<typename TWindow = Window>
    requires ( std::is_base_of_v<Window,TWindow> )
static inline TWindow* new_window(const Vector2& position, const Vector2& resolution) {
    TWindow* win = new TWindow(position,resolution);
    return new_window(win);
}

/* recommended to call, to prevent memory leaks */
static inline void clear_pool() {
    for(auto& i : window_pool) 
        if(i) {
            delete i;
            i = nullptr;
        }
    window_pool.clear();
}

template<typename TWindow = Window>
    requires ( std::is_base_of_v<Window,TWindow> )
static inline TWindow* get_window(const id_type& id) {
    for(auto& i : window_pool)
        if(i && i->get_id() == id) 
            return dynamic_cast<TWindow*>(i);
    return nullptr;
}

template<typename TWindow = Window>
    requires ( std::is_base_of_v<Window,TWindow> )
static inline TWindow* get_focused() {
    for(auto& i : window_pool) 
        if(i && i->focused()) 
            return dynamic_cast<TWindow*>(i);
    return nullptr;
}
template<typename TWindow = Window>
    requires ( std::is_base_of_v<Window,TWindow> )
static inline TWindow* next_handler(const key& skey) {
    for(auto& i : window_pool)
        if(i && !i->hidden() && (i->has_key(skey) || 
           i->get_key_check() && i->get_key_check()(skey)))
            return dynamic_cast<TWindow*>(i);
    return nullptr;
}

static inline void remove_window(Window* win) {
    if(!win) return;
    for(size_t i = 0; i < window_pool.size(); ++i)
        if(window_pool[i] == win) {
            window_pool.erase(window_pool.begin() + i);
            break;
        }
    delete win;
}

static inline void remove_window(const id_type& id) {
    remove_window(get_window(id));
}

static inline void init() {
    WINDOW* main = initscr();
    raw();
    nonl();
    noecho();
    nodelay(main, TRUE);
    keypad(main, TRUE);
    effect::color_init();
}

static inline void exit() {
    clear_pool();
    endwin();
}

}

#endif

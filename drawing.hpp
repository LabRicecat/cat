#ifndef CAT_DRAWING_HPP
#define CAT_DRAWING_HPP

#include <ncurses.h>
#include <vector>
#include <vector>
#include "window.hpp" 

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

static inline Window* new_window(Window* win) {
    window_pool.push_back(win);
    return win;
}

static inline Window* new_window(const Vector2& position, const Vector2& resolution) {
    Window* win = new Window(position,resolution);
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

static inline Window* get_window(const id_type& id) {
    for(auto& i : window_pool)
        if(i && i->get_id() == id) 
            return i;
    return nullptr;
}

static inline Window* get_focused() {
    for(auto& i : window_pool) 
        if(i && i->focused()) 
            return i;
    return nullptr;
}

static inline Window* next_handler(const key& skey) {
    for(auto& i : window_pool)
        if(i && !i->hidden() && (i->has_key(skey) || 
           i->get_key_check() && i->get_key_check()(skey)))
            return i;
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
    noecho();
    nodelay(main, TRUE);
    keypad(main, TRUE);
}

static inline void exit() {
    clear_pool();
    endwin();
}

}

#endif

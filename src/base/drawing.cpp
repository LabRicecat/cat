#include "../../inc/base/drawing.hpp"
#include "../../inc/base/effects.hpp"
#include "../../inc/base/container.hpp"

namespace cat {

/* it's adviced not to call this function frequently, 
   and let lifespan.cpp manage it */
void redraw() {
    auto cursor_pos = get_cursor();
    
    for(auto& i : window_pool)
        if(i && !i->hidden() && i->redraw_request) {
            for(auto& event : i->redraw_events)
                event(i);

            if(!current_settings.stuck_cursor || i->ncurses_window != cursor_pos.win)
                wrefresh(i->ncurses_window); // gets refreshed later
            i->redraw_request = false;
            i->trigger_syncs();
        }

    if(current_settings.stuck_cursor) {
        move_cursor(cursor_pos);
        wrefresh(cursor_pos.win);
    }
}

/* recommended to call, to prevent memory leaks */
void clear_pool() {
    for(auto& i : window_pool) 
        if(i) {
            delete i;
            i = nullptr;
        }
    window_pool.clear();
}

void unfocus() {
    Window* w;
    while((w = get_focused()) != nullptr)
        w->lose_focus();
}

void remove_window(const Window* win) {
    if(!win) return;
    for(size_t i = 0; i < window_pool.size(); ++i)
        if(window_pool[i] == win) {
            window_pool.erase(window_pool.begin() + i);
            break;
        }
    delete win;
}

void remove_window(const id_type& id) {
    remove_window(get_window(id));
}

void init() {
    WINDOW* main = initscr();
    raw();
    nonl();
    noecho();
    nodelay(main, TRUE);
    keypad(main, TRUE);
    effect::color_init();
}

void exit() {
    clear_pool();
    clear_container_pool();
    endwin();
}

} // namespace cat

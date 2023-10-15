#ifndef CAT_DRAWING_HPP
#define CAT_DRAWING_HPP

#include <ncurses.h>
#include <vector>
#include <vector>

#include "window.hpp"

namespace cat {

inline std::vector<Window*> window_pool;

/* it's adviced not to call this function frequently, 
   and let Lifespan.hpp manage it */
void redraw();

template<typename TWindow = Window>
    requires ( std::is_base_of_v<Window,TWindow> )
inline TWindow* new_window(TWindow* win) {
    window_pool.push_back((Window*)win);
    return win;
}

template<typename TWindow = Window>
    requires ( std::is_base_of_v<Window,TWindow> )
inline TWindow* new_window(const Vector2& position = {0,0}, const Vector2& resolution = {1,1}) {
    TWindow* win = new TWindow(position,resolution);
    return new_window(win);
}

/* recommended to call, to prevent memory leaks */
void clear_pool();

template<typename TWindow = Window>
    requires ( std::is_base_of_v<Window,TWindow> )
inline TWindow* get_window(const id_type& id) {
    for(auto& i : window_pool)
        if(i && i->get_id() == id) 
            return dynamic_cast<TWindow*>(i);
    return nullptr;
}

template<typename TWindow = Window>
    requires ( std::is_base_of_v<Window,TWindow> )
inline TWindow* get_focused() {
    for(auto& i : window_pool) 
        if(i && i->focused()) 
            return dynamic_cast<TWindow*>(i);
    return nullptr;
}

void unfocus();

template<typename TWindow = Window>
    requires ( std::is_base_of_v<Window,TWindow> )
inline TWindow* next_handler(const key& skey) {
    for(auto& i : window_pool)
        if(i && !i->hidden() && (i->has_key(skey) || 
           i->get_key_check() && i->get_key_check()(skey)))
            return dynamic_cast<TWindow*>(i);
    return nullptr;
}

void remove_window(const Window* win);
void remove_window(const id_type& id);

void init();
void exit();

} // namespace cat

#endif

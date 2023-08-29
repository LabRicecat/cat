#ifndef CAT_EFFECTS_HPP
#define CAT_EFFECTS_HPP

#include <string>
#include <functional>
#include <vector>
#include <ncurses.h>
#include <climits>

#include "string.hpp"
#include "id.hpp"

#ifndef CAT_USE_EXTENDED_COLORS
# define CAT_USE_EXTENDED_COLORS 1
#endif 

namespace cat {

struct Window;
namespace effect {
    using effect_t = CatString::fn_type;

    static inline const effect_t normal = 
        [](CatString&, WINDOW* w) { wattron(w, A_NORMAL); };
    static inline const effect_t standout = 
        [](CatString&, WINDOW* w) { wattron(w, A_STANDOUT); };
    static inline const effect_t underline = 
        [](CatString&, WINDOW* w) { wattron(w, A_UNDERLINE); };
    static inline const effect_t reverse = 
        [](CatString&, WINDOW* w) { wattron(w, A_REVERSE); };
    static inline const effect_t blink = 
        [](CatString&, WINDOW* w) { wattron(w, A_BLINK); };
    static inline const effect_t dim = 
        [](CatString&, WINDOW* w) { wattron(w, A_DIM); };
    static inline const effect_t bold = 
        [](CatString&, WINDOW* w) { wattron(w, A_BOLD); };
    static inline const effect_t protect = 
        [](CatString&, WINDOW* w) { wattron(w, A_PROTECT); };
    static inline const effect_t invisible = 
        [](CatString&, WINDOW* w) { wattron(w, A_INVIS); };
    static inline const effect_t altchar = 
        [](CatString&, WINDOW* w) { wattron(w, A_ALTCHARSET); };
#ifdef A_ITALIC 
    static inline const effect_t italic = 
        [](CatString&, WINDOW* w) { wattron(w, A_ITALIC); };
#else 
    static inline const effect_t italic = 
        [](CatString&, WINDOW* w) { };
#endif 

    struct rgb {
        int r = 0, g = 0, b = 0;
    };

    using color = id_type;
    using color_fg = short;
    using color_bg = color_fg;

    static inline bool colors_supported = false;
    static inline id_type i_color_id = 0;
    static inline id_type i_pair_id = 0;
        
    color new_color(const rgb& fg, const rgb& bg = rgb{-1,-1,-1});    
    color new_color(int r, int g, int b);    
    color new_color_pair(color_fg fg, color_bg bg);
    void color_init();
    
    namespace base_colors {
        static inline color black;
        static inline color red;
        static inline color green;
        static inline color yellow;
        static inline color blue;
        static inline color magenta;
        static inline color cyan;
        static inline color white;
    }

    namespace ncurses_colors {
        static inline color black;
        static inline color red;
        static inline color green;
        static inline color yellow;
        static inline color blue;
        static inline color magenta;
        static inline color cyan;
        static inline color white;
    }
    
    static inline const effect_t black = 
        [](CatString&, WINDOW* w) { wattron(w, COLOR_PAIR(base_colors::black)); };
    static inline const effect_t red = 
        [](CatString&, WINDOW* w) { wattron(w, COLOR_PAIR(base_colors::red)); };
    static inline const effect_t green = 
        [](CatString&, WINDOW* w) { wattron(w, COLOR_PAIR(base_colors::green)); };
    static inline const effect_t yellow = 
        [](CatString&, WINDOW* w) { wattron(w, COLOR_PAIR(base_colors::yellow)); };
    static inline const effect_t blue = 
        [](CatString&, WINDOW* w) { wattron(w, COLOR_PAIR(base_colors::blue)); };
    static inline const effect_t magenta = 
        [](CatString&, WINDOW* w) { wattron(w, COLOR_PAIR(base_colors::magenta)); };
    static inline const effect_t cyan = 
        [](CatString&, WINDOW* w) { wattron(w, COLOR_PAIR(base_colors::cyan)); };
    static inline const effect_t white = 
        [](CatString&, WINDOW* w) { wattron(w, COLOR_PAIR(base_colors::white)); };

    static inline effect_t custom(const color& c) {
        return [=](CatString&, WINDOW* w) { wattron(w, COLOR_PAIR(c)); };
    }
}

}

#endif

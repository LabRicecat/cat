#ifndef CAT_EFFECTS_HPP
#define CAT_EFFECTS_HPP

#include <string>
#include <functional>
#include <vector>
#include <ncurses.h>
#include <climits>

#include "string.hpp"
#include "id.hpp"
#include "settings.hpp"

namespace cat {

struct Window;
namespace effect {
    using effect_t = CatString::fn_type;

#define CAT_BLOCK_NOCOL(...) do if(current_settings.color) wattron(__VA_ARGS__); else { } while(0)

    inline const effect_t normal = 
        [](CatString&, WINDOW* w) { CAT_BLOCK_NOCOL(w, A_NORMAL); };
    inline const effect_t standout = 
        [](CatString&, WINDOW* w) { CAT_BLOCK_NOCOL(w, A_STANDOUT); };
    inline const effect_t underline = 
        [](CatString&, WINDOW* w) { CAT_BLOCK_NOCOL(w, A_UNDERLINE); };
    inline const effect_t reverse = 
        [](CatString&, WINDOW* w) { CAT_BLOCK_NOCOL(w, A_REVERSE); };
    inline const effect_t blink = 
        [](CatString&, WINDOW* w) { CAT_BLOCK_NOCOL(w, A_BLINK); };
    inline const effect_t dim = 
        [](CatString&, WINDOW* w) { CAT_BLOCK_NOCOL(w, A_DIM); };
    inline const effect_t bold = 
        [](CatString&, WINDOW* w) { CAT_BLOCK_NOCOL(w, A_BOLD); };
    inline const effect_t protect = 
        [](CatString&, WINDOW* w) { CAT_BLOCK_NOCOL(w, A_PROTECT); };
    inline const effect_t invisible = 
        [](CatString&, WINDOW* w) { CAT_BLOCK_NOCOL(w, A_INVIS); };
    inline const effect_t altchar = 
        [](CatString&, WINDOW* w) { CAT_BLOCK_NOCOL(w, A_ALTCHARSET); };
#ifdef A_ITALIC 
    inline const effect_t italic = 
        [](CatString&, WINDOW* w) { CAT_BLOCK_NOCOL(w, A_ITALIC); };
#else 
    inline const effect_t italic = 
        [](CatString&, WINDOW* w) { };
#endif 

    struct rgb {
        int r = 0, g = 0, b = 0;
    };

    using color = id_type;
    using color_fg = short;
    using color_bg = color_fg;

    inline bool colors_supported = false;
    inline id_type i_color_id = 0;
    inline id_type i_pair_id = 0;
        
    color new_color(const rgb& fg, const rgb& bg = rgb{-1,-1,-1});    
    color new_color(int r, int g, int b);    
    color new_color_pair(color_fg fg, color_bg bg);
    void color_init();
    
    namespace base_colors {
        inline color black;
        inline color red;
        inline color green;
        inline color yellow;
        inline color blue;
        inline color magenta;
        inline color cyan;
        inline color white;
    }

    namespace ncurses_colors {
        inline color black;
        inline color red;
        inline color green;
        inline color yellow;
        inline color blue;
        inline color magenta;
        inline color cyan;
        inline color white;
    }
    
    inline const effect_t black = 
        [](CatString&, WINDOW* w) { CAT_BLOCK_NOCOL(w, COLOR_PAIR(base_colors::black)); };
    inline const effect_t red = 
        [](CatString&, WINDOW* w) { CAT_BLOCK_NOCOL(w, COLOR_PAIR(base_colors::red)); };
    inline const effect_t green = 
        [](CatString&, WINDOW* w) { CAT_BLOCK_NOCOL(w, COLOR_PAIR(base_colors::green)); };
    inline const effect_t yellow = 
        [](CatString&, WINDOW* w) { CAT_BLOCK_NOCOL(w, COLOR_PAIR(base_colors::yellow)); };
    inline const effect_t blue = 
        [](CatString&, WINDOW* w) { CAT_BLOCK_NOCOL(w, COLOR_PAIR(base_colors::blue)); };
    inline const effect_t magenta = 
        [](CatString&, WINDOW* w) { CAT_BLOCK_NOCOL(w, COLOR_PAIR(base_colors::magenta)); };
    inline const effect_t cyan = 
        [](CatString&, WINDOW* w) { CAT_BLOCK_NOCOL(w, COLOR_PAIR(base_colors::cyan)); };
    inline const effect_t white = 
        [](CatString&, WINDOW* w) { CAT_BLOCK_NOCOL(w, COLOR_PAIR(base_colors::white)); };

    inline effect_t custom(const color& c) {
        return [=](CatString&, WINDOW* w) { CAT_BLOCK_NOCOL(w, COLOR_PAIR(c)); };
    }
}

#undef CAT_BLOCK_NOCOL

}

#endif

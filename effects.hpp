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
        
    static inline color new_color(const rgb& fg, const rgb& bg = rgb{-1,-1,-1}) {
        color colfg = ++i_color_id;
        color colbg = bg.r >= 0 ? ++i_color_id : COLOR_BLACK;
        init_extended_color(colfg, fg.r, fg.g, fg.b);
        if(bg.r >= 0) init_extended_color(colbg, bg.r, bg.g, bg.b);

        color pair = ++i_pair_id;

        auto f = init_extended_pair(pair, colfg, colbg);
        return pair;
    }
    static inline color new_color(int r, int g, int b) {
        return new_color({r, g, b});
    }
    
    static inline color new_color_pair(color_fg fg, color_bg bg) {
        color col = ++i_pair_id;
        init_pair(col, fg, bg);

        return col;
    }

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
    
    static inline void color_init() {
        if(!(colors_supported = can_change_color())) return;
        start_color();

#define NCORM * (1000 / 255)
#define NCOL(r, g, b) new_color(r NCORM, g NCORM, b NCORM )

        base_colors::black   = NCOL(0   ,0   ,0);
        base_colors::red     = NCOL(170 ,0   ,0);
        base_colors::green   = NCOL(0   ,170 ,0);
        base_colors::yellow  = NCOL(170 ,85  ,0);
        base_colors::blue    = NCOL(0   ,0   ,170);
        base_colors::magenta = NCOL(170 ,0   ,170);
        base_colors::cyan    = NCOL(0   ,170 ,170);
        base_colors::white   = NCOL(170 ,170 ,170);

#undef NCOL 
#undef NCORM 

        ncurses_colors::black   = new_color_pair(COLOR_BLACK,COLOR_BLACK);
        ncurses_colors::red     = new_color_pair(COLOR_RED,COLOR_BLACK);
        ncurses_colors::green   = new_color_pair(COLOR_GREEN,COLOR_BLACK);
        ncurses_colors::yellow  = new_color_pair(COLOR_YELLOW,COLOR_BLACK);
        ncurses_colors::blue    = new_color_pair(COLOR_BLUE,COLOR_BLACK);
        ncurses_colors::magenta = new_color_pair(COLOR_MAGENTA,COLOR_BLACK);
        ncurses_colors::cyan    = new_color_pair(COLOR_CYAN,COLOR_BLACK);
        ncurses_colors::white   = new_color_pair(COLOR_WHITE,COLOR_BLACK);
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
};

};

#endif

#include "../inc/effects.hpp"

namespace cat {

namespace effect {

color new_color(const rgb& fg, const rgb& bg) {
    color colfg = ++i_color_id;
    color colbg = bg.r >= 0 ? ++i_color_id : COLOR_BLACK;
    init_extended_color(colfg, fg.r, fg.g, fg.b);
    if(bg.r >= 0) init_extended_color(colbg, bg.r, bg.g, bg.b);

    color pair = ++i_pair_id;

    auto f = init_extended_pair(pair, colfg, colbg);
    return pair;
}
color new_color(int r, int g, int b) {
    return new_color({r, g, b});
}
    
color new_color_pair(color_fg fg, color_bg bg) {
    color col = ++i_pair_id;
    init_pair(col, fg, bg);

    return col;
}

void color_init() {
    if(!current_settings.color) return;
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
    
} // namespace effect

} // namespace cat 

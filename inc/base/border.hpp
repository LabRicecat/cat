#ifndef CAT_BASE_BORDER_HPP
#define CAT_BASE_BORDER_HPP

#include "string.hpp"
#include "unicode.hpp"

namespace cat {

class Window;
class Buffer;

struct Border {
    CatString top;
    CatString bottom;
    CatString left;
    CatString right;
    CatString corner_tl;
    CatString corner_tr;
    CatString corner_bl;
    CatString corner_br;

    const Border& apply(Window* window) const;
    //const Border& apply(Buffer* buffer) const;
    
    const Border& operator()(Window* window) const;
    //const Border& operator()(Buffer* buffer) const;
};

const inline Border light = {
    uc::horizontal_l,
    uc::horizontal_l,
    uc::vertical_l,
    uc::vertical_l,
    uc::corner_ll_left_up,
    uc::corner_ll_right_up,
    uc::corner_ll_left_down,
    uc::corner_ll_right_up
};

const inline Border heavy = {
    uc::horizontal_h,
    uc::horizontal_h,
    uc::vertical_h,
    uc::vertical_h,
    uc::corner_hh_left_up,
    uc::corner_hh_right_up,
    uc::corner_hh_left_down,
    uc::corner_hh_right_up
};

} // namespace cat

#endif

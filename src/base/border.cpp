#include "../../inc/base/border.hpp"
#include "../../inc/base/window.hpp"
#include "../../inc/base/buffer.hpp"

namespace cat {

const Border& Border::apply(Window* window) const {
    for(Vector2::value_type x = 1; x < window->get_resolution().x-1; ++x)
        window->draw_at({x, 0}, top),
        window->draw_at({x, window->get_resolution().y-1}, bottom);
    
    for(Vector2::value_type y = 1; y < window->get_resolution().y-1; ++y)
        window->draw_at({0, y}, left),
        window->draw_at({window->get_resolution().x-1, y}, right);

    window->draw_at({0, 0}, corner_tl);
    window->draw_at({0, window->get_resolution().y-1}, corner_tr);

    window->draw_at({window->get_resolution().y-1, 0}, corner_bl);
    window->draw_at({window->get_resolution().y-1, window->get_resolution().x-1}, corner_bl);

    return *this;
}

const Border& Border::operator()(Window* window) const {
    return apply(window);
}

} // namespace cat 

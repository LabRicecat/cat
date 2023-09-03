#include "../../inc/library/renderers.hpp"

namespace cat {

namespace lib {

Renderer::return_type fit_hight(const Renderer::param_type& param, Buffer* buffer) {
    image_type rimage;
    Vector2 res = buffer->window()->get_resolution();
    Vector2::value_type hight = 1;
        
    for(auto& i : param) {
        if(i == '\n') 
            ++hight;
        if(hight > res.y)
             break;
        rimage += i;
    }

    return rimage;
}

Renderer::return_type fit_width(const Renderer::param_type& param, Buffer* buffer) {
    image_type rimage;
    Vector2 res = buffer->window()->get_resolution();
    Vector2::value_type width = 0;
        
    for(auto& i : param) {
        ++width;
        if(i == '\n') 
            width = 0;
        if(width <= res.x)
            rimage += i;
    }

    return rimage;
}

} // namespace lib

} // namespace cat 

#ifndef CAT_LIBRARY_RENDERERS_HPP
#define CAT_LIBRARY_RENDERERS_HPP

#include "../buffer.hpp"
#include "../window.hpp"

namespace cat {

namespace lib {

    Renderer::return_type fit_hight(const Renderer::param_type& param, Buffer* buffer);

    Renderer::return_type fit_width(const Renderer::param_type& param, Buffer* buffer);

} // namespace lib

} // namespace cat

#endif 

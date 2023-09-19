#ifndef CAT_RENDERER_FIT_HPP
#define CAT_RENDERER_FIT_HPP

#include "../base/buffer.hpp"

namespace cat {

    Renderer::return_type fit_hight(const Renderer::param_type& param, Buffer* buffer);

    Renderer::return_type fit_width(const Renderer::param_type& param, Buffer* buffer);

} // namespace cat

#endif

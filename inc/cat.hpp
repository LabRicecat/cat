#ifndef CAT_TUI_HPP
#define CAT_TUI_HPP

/* the whole TUI framework */ 

#define CAT_VERSION 000201

// requires C++20
#if __cplusplus >= 202002

#include "base.hpp"

#ifndef CAT_BASE_ONLY

#include "buffer/lockable.hpp"
#include "buffer/scrollable.hpp"

#include "composer/linenumbers.hpp"

#include "container/horizontal.hpp"

#include "renderer/fit.hpp"

#include "window/inputfield.hpp"
#include "window/textfield.hpp"

#endif 

#else
# error "CAT requires C++ version 20 !"
#endif 

#endif

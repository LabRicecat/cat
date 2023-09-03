#ifndef CAT_TUI_HPP
#define CAT_TUI_HPP

/* the whole TUI framework */ 

#define CAT_VERSION 000100

// requires C++20
#if __cplusplus >= 202002

#include "buffer.hpp"
#include "config.hpp"
#include "container.hpp"
#include "drawcalls.hpp"
#include "drawing.hpp"
#include "effects.hpp"
#include "id.hpp"
#include "input.hpp"
#include "library.hpp"
#include "lifespan.hpp"
#include "settings.hpp"
#include "signals.hpp"
#include "string.hpp"
#include "string_iterator.hpp"
#include "terminal.hpp"
#include "vector.hpp"
#include "window.hpp"

#include "library/buffers.hpp"
#include "library/composers.hpp"
#include "library/containers.hpp"
#include "library/renderers.hpp"
#include "library/windows.hpp"

#else
# error "CAT requires C++ version 20 !"
#endif 

#endif

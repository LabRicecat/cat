#ifndef CAT_SIGNALS_HPP
#define CAT_SIGNALS_HPP

#include <string>
#include <functional>
#include <vector>

namespace cat {

namespace signals {
    using msg_signal = std::string;
    using switch_signal = bool;


    static inline switch_signal quit = false;
    static inline msg_signal error = "";
}

using error_handler = std::function<void()>;
static inline std::vector<error_handler> error_handlers;

static inline void on_error(const error_handler& handler) {
    error_handlers.push_back(handler);
}

static inline void error(const std::string& msg) {
    signals::error = msg;
    for(auto& i : error_handlers)
        i();
}

}

#endif

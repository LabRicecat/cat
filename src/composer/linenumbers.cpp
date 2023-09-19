#include "../../inc/composer/linenumbers.hpp"

namespace cat {

Composer::return_type line_numbers(const Composer::param_type& snippet, Buffer* buffer) {
    Composer::param_type rimage = "1 | ";
    size_t line = 1;

    for(auto& i : snippet) {
        rimage += i;
        if(i == '\n')
            rimage += std::to_string(++line) + " | ";
    }

    return rimage;
}

} // namespace cat

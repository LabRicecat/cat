#include "../../inc/library/composers.hpp"

namespace cat {

namespace lib {

Composer::return_type line_numbers(const Composer::param_type& snippet, Buffer* buffer) {
    image_type rimage = "1 | ";
    size_t line = 1;

    for(auto& i : snippet) {
        rimage += i;
        if(i == '\n')
            rimage += std::to_string(++line) + " | ";
    }

    return rimage;
}

} // namespace lib

} // namespace cat

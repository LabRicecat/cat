#include "../../inc/window/textfield.hpp" 

namespace cat {

TextField& TextField::append(const CatString& str) {
    get_buffer()->get_raw().push_back(str);
    idx += str.size();
    curs_position += Vector2(idx, 0);
    return *this;
}

TextField& TextField::clear_text() {
    get_buffer()->get_raw() = "";
    idx = 0;
    curs_position = {0,0};
    return *this;
}

CatString& TextField::get() {
    return get_buffer()->get_raw();
}

} // namespace cat

#include "../../inc/library/containers.hpp"

namespace cat {

namespace lib {

Vector2::value_type div_error(Vector2::value_type a, Vector2::value_type b) {
    return a - ((a / b) * b);
}

Container& HorizontalContainer::apply() {
    if(entries() == 0) return *this;
    const Vector2::value_type win_x = get_resolution().x / entries();
    
    for(size_t i = 0; i < windows.size(); ++i) {
        windows[i]->clear();
        windows[i]->move({ get_position().x + win_x * (Vector2::value_type)i, get_position().y });
        windows[i]->resize({ win_x, get_resolution().y });

        // appends missing size to last window
        if(i+1 == windows.size())
            windows[i]->resize({
                    windows[i]->get_resolution().x + div_error(get_resolution().x, entries()),
                    get_resolution().y
                });
    }

    Container::apply();
    return *this;
}

} // namespace lib

} // namespace cat

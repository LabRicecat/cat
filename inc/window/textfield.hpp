#ifndef CAT_WINDOW_TEXTFIELD_HPP
#define CAT_WINDOW_TEXTFIELD_HPP 

#include "../base/window.hpp"

namespace cat {

class TextField : public Window {
    Vector2 curs_position;
    size_t idx = 0;

public:
    TextField(const Vector2& position, const Vector2& resolution)
    : Window::Window(position,resolution) {
        key_check = [](const key& k) { return isprint(k); };
        key_handler = [&](const key& k) {
            buffer->get_raw().append(std::string(1,(char)k));
            ++idx;
            curs_position += Vector2{1,0};

            clear();
            draw_buffer();
            redraw();
        };
    }

    virtual TextField& append(const CatString& str);
    virtual TextField& clear_text();
    virtual CatString& get();

};

} // namespace cat

#endif

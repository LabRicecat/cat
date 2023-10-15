#ifndef CAT_LIBRARY_WINDOWS_HPP
#define CAT_LIBRARY_WINDOWS_HPP

#include "../window.hpp"

namespace cat {

namespace lib {

class InputField : public Window {
    Vector2 curs_position;
    size_t idx = 0;

    bool check_boundary(const Vector2& mov) {
        return 
            (curs_position + mov).x >= 0 &&
            (curs_position + mov).y >= 0 &&
            (curs_position + mov).x <= get_resolution().x &&
            (curs_position + mov).y <= get_resolution().y &&

            (curs_position + mov).y * get_resolution().y +
            (curs_position + mov).x < idx;
    }

public:
    InputField(const Vector2& position, const Vector2& resolution)
    : Window::Window(position,resolution) {
        set_buffer<Buffer>();

        key_check = [](const key& k) { return isprint(k); };
        key_handler = [&](const key& k) {
            buffer->get_raw().insert(idx, (std::string(1,(char)k)));
            ++idx;
            curs_position += Vector2{1,0};
            clear();
            draw_buffer();
            redraw();
        };

        set_key(KEY_LEFT, [&]() {
            if(check_boundary({-1,0})) 
                --curs_position.x;
            else if(check_boundary({0,-1}))
                --curs_position.y, curs_position.x = 0;
            
            cursor(curs_position);
            clear();
            draw_buffer();
            redraw();
        });

        set_key(KEY_RIGHT, [&]() {
            if(check_boundary({+1,0})) 
                ++curs_position.x;
            else if(check_boundary({0,+1}))
                ++curs_position.y, curs_position.x = 0;
            
            cursor(curs_position);
            clear();
            draw_buffer();
            redraw();
        });

        set_key('\n', [&]() {
            if(check_boundary({0,+1})) 
                ++curs_position.y, ++idx;
            cursor(curs_position);
            clear();
            draw_buffer();
            redraw();
        });
        
        set_key(KEY_BACKSPACE, [&]() {
            draw_at(curs_position, " ");
            if(check_boundary({-1,0}))
                --curs_position.x, --idx;
            else if(check_boundary({0,-1}))
                --curs_position.y, curs_position.x = 0, --idx;
            
            cursor(curs_position);
            clear();
            draw_buffer();
            redraw();
        });

    }
};

class BasicShell : public Window {
    using Window::Window;

   // TODO: test the framework 
};

} // namespace lib

} // namespace cat

#endif

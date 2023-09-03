#ifndef CAT_LIBRARY_WINDOWS_HPP
#define CAT_LIBRARY_WINDOWS_HPP

#include "../window.hpp"

namespace cat {

namespace lib {

class InputField : public Window {
public:
    InputField(const Vector2& position, const Vector2& resolution)
    : Window::Window(position,resolution) {
        this->set_buffer<Buffer>();
        this->key_check = [](const key& k) { return isascii(k); };
        this->key_handler = [&](const key& k) { 
            this->buffer->append(std::string(1,(char)k));
            this->draw_buffer();
            this->redraw();
        };

        this->set_key(cat::shift('c'),[&]() {
           this->buffer->clear();
           this->redraw();
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

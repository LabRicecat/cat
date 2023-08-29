#ifndef CAT_LIBRARY_HPP
#define CAT_LIBRARY_HPP

#include "window.hpp" 
#include "buffer.hpp"
#include <cwctype>

namespace cat {

namespace composers {
    static inline  Composer line_numbers = [](const Composer::param_type& snippet, Buffer* buffer)->Composer::return_type {
        image_type rimage = "1 | ";
        size_t line = 1;

        for(auto& i : snippet) {
            rimage += i;
            if(i == '\n')
                rimage += std::to_string(++line) + " | ";
        }

        return rimage;
    };
}

namespace renderers {
    static inline Renderer fit_hight = [](const image_type& image, Buffer* buffer)->image_type {
        image_type rimage;
        Vector2 res = buffer->window()->get_resolution();
        Vector2::value_type hight = 1;
        
        for(auto& i : image) {
            if(i == '\n') 
                ++hight;
            if(hight > res.y)
                break;
            rimage += i;
        }

        return rimage;
    };

    static inline Renderer fit_width = [](const image_type& image, Buffer* buffer)->image_type {
        image_type rimage;
        Vector2 res = buffer->window()->get_resolution();
        Vector2::value_type width = 0;
        
        for(auto& i : image) {
            ++width;
            if(i == '\n') 
                width = 0;
            if(width <= res.x)
                rimage += i;
        }

        return rimage;
    };
}

class LockableBuffer : virtual public Buffer {
protected:
    bool is_locked = false;
    image_type last_display;
public:
    using Buffer::Buffer;

    virtual LockableBuffer& lock() { 
        is_locked = true;
        return *this;
    }

    virtual LockableBuffer& unlock() {
        is_locked = false;
        return *this;
    }

    virtual bool locked() {
        return is_locked;
    }

    virtual image_type display() override {
        if(locked())
            return last_display;
        else 
            return last_display = Buffer::display();
    }
};

class ScrollBuffer : virtual public Buffer {
    uint64_t position = 0;

    virtual snippet_type generate_snippet() override {
        return raw.substr(position);
    }
public:
    using Buffer::Buffer;
    
    ScrollBuffer& advance() {
        while(position < raw.size() && raw[position] != '\n')
            ++position;
        if(raw[position] == '\n') ++position;
        
        return *this;
    }

    ScrollBuffer& back() {
        if(position == 0) return *this;
        position -= 2;
        while(position != 0 && raw[position] != '\n')
            --position;

        return *this;
    }
};

class BoxedWindow : public Window {
    bool is_boxed = false;
public:
    using Window::Window;

    virtual BoxedWindow& box(int chtype) override {
        Window::box(chtype);
        is_boxed = true;
        return *this;
    }

    virtual bool boxed() { return is_boxed; }
};

class InputFieldWindow : public Window {
public:
    InputFieldWindow(const Vector2& position, const Vector2& resolution)
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


}
#endif

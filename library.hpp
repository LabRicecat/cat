#ifndef CAT_LIBRARY_HPP
#define CAT_LIBRARY_HPP

#include "window.hpp" 
#include "buffer.hpp"
#include <cwctype>

namespace cat {

namespace processors {
       
}

namespace renderers {
    static inline Buffer::image_type fit_resolution_hight(const Buffer::image_type& image, Buffer* buffer) {
        Buffer::image_type rimage;
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
    }
    
    
    static inline Buffer::renderer_type compose(const Buffer::renderer_type& render) {
        return render;
    }

    template<typename Tr0, typename Tr1, typename... TrTail>
    static inline Buffer::renderer_type compose(const Tr0& r0, const Tr1& r1, const TrTail& ...tail) {
        return [=](const Buffer::image_type& image, Buffer* buffer)->Buffer::image_type{ return r0(compose(r1,tail...)(image, buffer),buffer); };
    }
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

class BasicShell : public Window {
    using Window::Window;

   // TODO: test the framework 
};


}
#endif

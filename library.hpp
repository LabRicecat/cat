#ifndef CAT_LIBRARY_HPP
#define CAT_LIBRARY_HPP

#include "window.hpp" 
#include "buffer.hpp"

namespace cat {

class LockableBuffer : public Buffer {
protected:
    bool is_locked = false;
public:
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
};

class ScrollBuffer : public Buffer {
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

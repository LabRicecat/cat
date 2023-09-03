#include "../../inc/library/buffers.hpp"

namespace cat {

namespace lib {

LockableBuffer& LockableBuffer::unlock() {
    is_locked = false;
    return *this;
}

bool LockableBuffer::locked() {
    return is_locked;
}

image_type LockableBuffer::display() {
    if(locked())
        return last_display;
    else 
        return last_display = Buffer::display();
}

snippet_type ScrollBuffer::generate_snippet() {
    return raw.substr(position);
}

ScrollBuffer& ScrollBuffer::advance() {
    while(position < raw.size() && raw[position] != '\n')
        ++position;
    if(raw[position] == '\n') ++position;
        
    return *this;
}

ScrollBuffer& ScrollBuffer::back() {
    if(position == 0) return *this;
    position -= 2;
    while(position != 0 && raw[position] != '\n')
        --position;

    return *this;
}

} // namespace lib

} // namespace cat

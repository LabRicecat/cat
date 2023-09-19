#include "../../inc/buffer/lockable.hpp"

namespace cat {

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

} // namespace cat

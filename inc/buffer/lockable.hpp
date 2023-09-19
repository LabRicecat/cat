#ifndef CAT_BUFFER_LOCKABLE_HPP
#define CAT_BUFFER_LOCKABLE_HPP

#include "../base/buffer.hpp"

namespace cat {

class LockableBuffer : virtual public Buffer {
protected:
    bool is_locked = false;
    image_type last_display;
public:
    using Buffer::Buffer;

    virtual LockableBuffer& lock();

    virtual LockableBuffer& unlock();

    virtual bool locked();

    virtual image_type display() override;
};

} // namespace cat 

#endif 

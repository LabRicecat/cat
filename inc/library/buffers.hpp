#ifndef CAT_LIBRARY_BUFFERS_HPP
#define CAT_LIBRARY_BUFFERS_HPP

#include "../buffer.hpp"

namespace cat {

namespace lib {

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

class ScrollBuffer : virtual public Buffer {
    uint64_t position = 0;

    virtual snippet_type generate_snippet() override;
public:
    using Buffer::Buffer;
    
    virtual ScrollBuffer& advance();

    virtual ScrollBuffer& back();
};

} // namespace lib

} // namespace cat 

#endif 

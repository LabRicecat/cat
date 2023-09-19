#ifndef CAT_BUFFER_SCROLLABLE_HPP
#define CAT_BUFFER_SCROLLABLE_HPP

#include "../base/buffer.hpp"

namespace cat {

class ScrollableBuffer : virtual public Buffer {
    uint64_t position = 0;

    virtual snippet_type generate_snippet() override;
public:
    using Buffer::Buffer;
    
    virtual ScrollableBuffer& advance();

    virtual ScrollableBuffer& back();
};

} // namespace cat 

#endif 

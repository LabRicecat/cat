#include "../../inc/buffer/scrollable.hpp"

namespace cat {

snippet_type ScrollableBuffer::generate_snippet() {
    return raw.substr(position);
}

ScrollableBuffer& ScrollableBuffer::advance() {
    while(position < raw.size() && raw[position] != '\n')
        ++position;
    if(raw[position] == '\n') ++position;
        
    return *this;
}

ScrollableBuffer& ScrollableBuffer::back() {
    if(position == 0) return *this;
    position -= 2;
    while(position != 0 && raw[position] != '\n')
        --position;

    return *this;
}

} // namespace cat

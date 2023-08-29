#include "../inc/buffer.hpp"

namespace cat {

snippet_type Buffer::generate_snippet() {
    return raw; // to implement by the derived classes
}

Window* Buffer::window() {
    return assoc_window;
}

Buffer& Buffer::set(const std::string& raw) {
    get_raw() = raw;
    return *this;
}

Buffer& Buffer::append(const std::string& raw) {
    get_raw() += raw;
    return *this;
}

std::string& Buffer::get_raw() {
    return raw;
}

Buffer& Buffer::clear() {
    get_raw() = "";
    return *this;
}

Composer& Buffer::composer() { return i_composer; }
Renderer& Buffer::renderer() { return i_renderer; }

image_type Buffer::display() {
    return i_renderer(
        i_composer(
            generate_snippet(),
        this),
    this);
}

} // namespace cat

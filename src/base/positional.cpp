#include "../../inc/base/positional.hpp" 

namespace cat {

Vector2 Positional::get_position() {
    return position;
}

Vector2 Positional::get_resolution() {
    return resolution;
}

Positional& Positional::move(const Vector2& position) {
    this->position = position;
    return *this;
}

Positional& Positional::resize(const Vector2& resolution) {
    this->resolution = resolution;
    return *this;
}

} // namespace cat

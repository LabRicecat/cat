#ifndef CAT_POSITIONAL_HPP
#define CAT_POSITIONAL_HPP

#include "vector.hpp"

namespace cat {

class Positional {
protected:
    Vector2 position;
    Vector2 resolution;
public:
    Positional() = delete;
    Positional(const Vector2& position, const Vector2& resolution)
    : position(position), resolution(resolution) { }

    virtual Vector2 get_position();
    virtual Vector2 get_resolution();

    virtual Positional& move(const Vector2& position);
    virtual Positional& resize(const Vector2& positional);
};

} // namespace cat

#endif 

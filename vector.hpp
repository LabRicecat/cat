#ifndef CAT_VECTOR_HPP
#define CAT_VECTOR_HPP 

#include <cstdint>
#include <cmath>

namespace cat {

struct Vector2 {
    using value_type = uint32_t;
    value_type x = 0;
    value_type y = 0;

    Vector2() { }
    Vector2(value_type x, value_type y)
    : x(x), y(y) { }

    Vector2 operator+(const Vector2& v)
    { return Vector2(x + v.x, y + v.y); }

    Vector2 operator-(const Vector2& v) 
    { return Vector2(x - v.x, y - v.y); }

    Vector2 operator*(const Vector2& v)
    { return Vector2(x * v.x, y * v.y); }

    Vector2 operator/(const Vector2& v) 
    { return Vector2(x / v.x, y / v.y); }

    Vector2& operator+=(const Vector2& v) 
    { x += v.x, y += v.y; return *this; }

    Vector2& operator-=(const Vector2& v)
    { x -= v.x, y -= v.y; return *this; }

    Vector2& operator*=(const Vector2& v)
    { x *= v.x, y *= v.y; return *this; }

    Vector2& operator/=(const Vector2& v)
    { x /= v.x, y /= v.y; return *this; }

    value_type distance(const Vector2& v)
    { return (value_type) std::sqrt( std::pow(x - v.x,2) + std::pow(y - v.y,2) ); }

    bool between(const Vector2& a, const Vector2& b) { 
        return std::max(a.x,b.x) <= x
            && std::min(a.x,b.x) >= x 
            && std::max(a.y,b.y) <= y 
            && std::min(a.y,b.y) >= y;
    }
};

}

#endif

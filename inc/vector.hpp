#ifndef CAT_VECTOR_HPP
#define CAT_VECTOR_HPP 

#include <cstdint>
#include <cmath>

namespace cat {

struct Vector2 {
    using value_type = int64_t;
    value_type x = 0;
    value_type y = 0;

    Vector2() { }
    Vector2(value_type x, value_type y)
    : x(x), y(y) { }

    Vector2 operator+(const Vector2& v);
    Vector2 operator-(const Vector2& v);
    Vector2 operator*(const Vector2& v);
    Vector2 operator/(const Vector2& v);

    Vector2& operator+=(const Vector2& v);
    Vector2& operator-=(const Vector2& v);
    Vector2& operator*=(const Vector2& v);
    Vector2& operator/=(const Vector2& v);

    value_type distance(const Vector2& v);

    bool between(const Vector2& a, const Vector2& b); 
};

} // namespace cat

#endif

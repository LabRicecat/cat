#include "../inc/vector.hpp"

namespace cat {

Vector2 Vector2::operator+(const Vector2& v)
{ return Vector2(x + v.x, y + v.y); }

Vector2 Vector2::operator-(const Vector2& v) 
{ return Vector2(x - v.x, y - v.y); }

Vector2 Vector2::operator*(const Vector2& v)
{ return Vector2(x * v.x, y * v.y); }

Vector2 Vector2::operator/(const Vector2& v) 
{ return Vector2(x / v.x, y / v.y); }

Vector2& Vector2::operator+=(const Vector2& v) 
{ x += v.x, y += v.y; return *this; }

Vector2& Vector2::operator-=(const Vector2& v)
{ x -= v.x, y -= v.y; return *this; }

Vector2& Vector2::operator*=(const Vector2& v)
{ x *= v.x, y *= v.y; return *this; }

Vector2& Vector2::operator/=(const Vector2& v)
{ x /= v.x, y /= v.y; return *this; }

Vector2::value_type Vector2::distance(const Vector2& v)
{ return (Vector2::value_type) std::sqrt( std::pow(x - v.x,2) + std::pow(y - v.y,2) ); }

bool Vector2::between(const Vector2& a, const Vector2& b) { 
    return std::max(a.x,b.x) <= x
        && std::min(a.x,b.x) >= x 
        && std::max(a.y,b.y) <= y 
        && std::min(a.y,b.y) >= y;
}

} // namespace cat 

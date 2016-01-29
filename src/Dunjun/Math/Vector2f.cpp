#include <cmath>
#include <ostream>

#include <Dunjun/Math/Vector2f.hpp>

namespace Dunjun {

Vector2f::Vector2f() : x(0), y(0) {}
Vector2f::Vector2f(float a) : x(a), y(a) {}
Vector2f::Vector2f(float x, float y) : x(x), y(y) {}
Vector2f::Vector2f(float xy[2]) : x(xy[0]), y(xy[1]) {}

inline Vector2f Vector2f::operator+(const Vector2f& other) const {
  return Vector2f(x + other.x, y + other.y);
}

inline Vector2f Vector2f::operator-(const Vector2f& other) const {
  return Vector2f(x - other.x, y - other.y);
}

inline Vector2f& Vector2f::operator+=(const Vector2f& other) {
  x += other.x;
  y += other.y;
  return *this;
}

inline Vector2f& Vector2f::operator-=(const Vector2f& other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

inline Vector2f Vector2f::operator*(const float s) const {
  return Vector2f(x * s, y * s);
}

inline Vector2f& Vector2f::operator*=(const float s) {
  x *= s;
  y *= s;
  return *this;
}

inline Vector2f Vector2f::operator/(const float s) const {
  return Vector2f(x / s, y / s);
}

inline Vector2f& Vector2f::operator/=(const float s) {
  x /= s;
  y /= s;
  return *this;
}

inline float Vector2f::length() { return std::sqrt(x * x + y * y); }
inline float Vector2f::lengthSquared() { return x * x + y * y; }
inline Vector2f Vector2f::normalized() { return *this / length(); }
inline float Vector2f::dot(const Vector2f& v) const {
  return x * v.x + y * v.y;
}
inline float Vector2f::cross(const Vector2f& v) const {
  return x * v.y - y * v.x;
}

inline bool Vector2f::operator==(const Vector2f& other) const {
  return x == other.x && y == other.y;
}

inline bool Vector2f::operator!=(const Vector2f& other) const {
  return !(*this == other);
}

inline Vector2f operator*(const float s, const Vector2f& v) { return v * s; }

inline std::ostream& operator<<(std::ostream& os, const Vector2f& v) {
  return os << "Vector2f (" << v.x << ", " << v.y << ")";
}

} // namespace Dunjun

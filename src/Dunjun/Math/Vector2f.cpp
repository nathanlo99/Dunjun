#include <cmath>
#include <ostream>

#include <Dunjun/Math/Vector2f.hpp>

namespace Dunjun {

Vector2f::Vector2f() : x(0), y(0) {}
Vector2f::Vector2f(const float x, const float y) : x(x), y(y) {}
Vector2f::Vector2f(const float xy[2]) : x(xy[0]), y(xy[1]) {}

Vector2f Vector2f::operator+(const Vector2f& other) const {
  return Vector2f(x + other.x, y + other.y);
}

Vector2f Vector2f::operator-(const Vector2f& other) const {
  return Vector2f(x - other.x, y - other.y);
}

Vector2f& Vector2f::operator+=(const Vector2f& other) {
  x += other.x;
  y += other.y;
  return *this;
}

Vector2f& Vector2f::operator-=(const Vector2f& other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

Vector2f Vector2f::operator*(const float s) const {
  return Vector2f(x * s, y * s);
}

Vector2f& Vector2f::operator*=(const float s) {
  x *= s;
  y *= s;
  return *this;
}

Vector2f Vector2f::operator/(const float s) const {
  return Vector2f(x / s, y / s);
}

Vector2f& Vector2f::operator/=(const float s) {
  x /= s;
  y /= s;
  return *this;
}

float Vector2f::length() const { return sqrtf(x * x + y * y); }
float Vector2f::lengthSquared() const { return x * x + y * y; }
Vector2f Vector2f::normalize() const { return *this / length(); }
float Vector2f::dot(const Vector2f& v) const { return x * v.x + y * v.y; }
float Vector2f::cross(const Vector2f& v) const { return x * v.y - y * v.x; }

bool Vector2f::operator==(const Vector2f& other) const {
  return x == other.x && y == other.y;
}

bool Vector2f::operator!=(const Vector2f& other) const {
  return !(*this == other);
}

Vector2f operator*(const float s, const Vector2f& v) { return v * s; }

std::ostream& operator<<(std::ostream& os, const Vector2f& v) {
  return os << "Vector2f (" << v.x << ", " << v.y << ")";
}

} // namespace Dunjun

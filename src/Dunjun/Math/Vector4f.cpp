#include <ostream>
#include <cmath>

#include <Dunjun/Math/Vector4f.hpp>

namespace Dunjun {

Vector4f::Vector4f() : x(0), y(0), z(0), w(0) {}
Vector4f::Vector4f(const float x, const float y, const float z, const float w)
: x(x), y(y), z(z), w(w) {}
Vector4f::Vector4f(const float xy[4])
: x(xy[0]), y(xy[1]), z(xy[2]), w(xy[3]) {}

Vector4f Vector4f::operator+(const Vector4f& other) const {
  return Vector4f(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4f Vector4f::operator-(const Vector4f& other) const {
  return Vector4f(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vector4f& Vector4f::operator+=(const Vector4f& other) {
  x += other.x;
  y += other.y;
  z += other.z;
  w += other.w;
  return *this;
}

Vector4f& Vector4f::operator-=(const Vector4f& other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
  w -= other.w;
  return *this;
}

Vector4f Vector4f::operator*(const float s) const {
  return Vector4f(s * x, s * y, s * z, s * w);
}

Vector4f& Vector4f::operator*=(const float s) {
  x *= s;
  y *= s;
  z *= s;
  w *= s;
  return *this;
}

Vector4f Vector4f::operator/(const float s) const {
  return Vector4f(x / s, y / s, z / s, w / s);
}

Vector4f& Vector4f::operator/=(const float s) {
  x /= s;
  y /= s;
  z /= s;
  w /= s;
  return *this;
}

float Vector4f::length() const { return sqrtf(x * x + y * y + z * z + w * w); }

float Vector4f::lengthSquared() const { return x * x + y * y + z * z + w * w; }

Vector4f Vector4f::normalize() const { return *this / length(); }

float Vector4f::dot(const Vector4f& v) const {
  return x * v.x + y * v.y + z * v.z + w * v.w;
}

bool Vector4f::operator==(const Vector4f& other) const {
  return x == other.x && y == other.y && other.z == z && other.w == w;
}

bool Vector4f::operator!=(const Vector4f& other) const {
  return !(*this == other);
}

Vector4f operator*(const float s, const Vector4f& v) { return v * s; }

std::ostream& operator<<(std::ostream& os, const Vector4f& v) {
  return os << "Vector4f(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w
            << ")";
}

} // namespace Dunjun

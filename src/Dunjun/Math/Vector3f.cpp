#include <ostream>
#include <cmath>
#include <Dunjun/Math/Vector3f.hpp>

namespace Dunjun {
Vector3f::Vector3f() : x(0), y(0), z(0) {}
Vector3f::Vector3f(const float x, const float y, const float z)
: x(x), y(y), z(z) {}
Vector3f::Vector3f(const float xy[3]) : x(xy[0]), y(xy[1]), z(xy[2]) {}

Vector3f Vector3f::operator+(const Vector3f& other) const {
  return Vector3f(x + other.x, y + other.y, z + other.z);
}

Vector3f Vector3f::operator-(const Vector3f& other) const {
  return Vector3f(x - other.x, y - other.y, z - other.z);
}

Vector3f& Vector3f::operator+=(const Vector3f& other) {
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

Vector3f& Vector3f::operator-=(const Vector3f& other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}

Vector3f Vector3f::operator*(const float s) const {
  return Vector3f(s * x, s * y, s * z);
}

Vector3f& Vector3f::operator*=(const float s) {
  x *= s;
  y *= s;
  z *= s;
  return *this;
}

Vector3f Vector3f::operator/(const float s) const {
  return Vector3f(x / s, y / s, z / s);
}

Vector3f& Vector3f::operator/=(const float s) {
  x /= s;
  y /= s;
  z /= s;
  return *this;
}

float Vector3f::length() const { return sqrtf(x * x + y * y + z * z); }

float Vector3f::lengthSquared() const { return x * x + y * y + z * z; }
Vector3f Vector3f::normalize() const { return *this / length(); }

float Vector3f::dot(const Vector3f& v) const {
  return x * v.x + y * v.y + z * v.z;
}

Vector3f Vector3f::cross(const Vector3f& v) const {
  return Vector3f(y * v.z - v.y * z, z * v.x - v.z * x, x * v.y - v.x * y);
}

bool Vector3f::operator==(const Vector3f& other) const {
  return x == other.x && y == other.y && z == other.z;
}

bool Vector3f::operator!=(const Vector3f& other) const {
  return !(*this == other);
}

Vector3f operator*(const float s, const Vector3f& v) { return v * s; }

std::ostream& operator<<(std::ostream& os, const Vector3f& v) {
  return os << "Vector3f (" << v.x << ", " << v.y << ", " << v.z << ")";
}

} // namespace Dunjun

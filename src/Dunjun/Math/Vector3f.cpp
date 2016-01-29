#include <ostream>
#include <cmath>
#include <Dunjun/Math/Vector3f.hpp>

namespace Dunjun {
Vector3f::Vector3f() : x(0), y(0), z(0) {}
Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}
Vector3f::Vector3f(float xy[3]) : x(xy[0]), y(xy[1]), z(xy[2]) {}
Vector3f::Vector3f(float a) : x(a), y(a), z(a) {}

inline Vector3f Vector3f::operator+(const Vector3f& other) const {
  return Vector3f(x + other.x, y + other.y, z + other.z);
}

inline Vector3f Vector3f::operator-(const Vector3f& other) const {
  return Vector3f(x - other.x, y - other.y, z - other.z);
}

inline Vector3f& Vector3f::operator+=(const Vector3f& other) {
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

inline Vector3f& Vector3f::operator-=(const Vector3f& other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}

inline Vector3f Vector3f::operator*(const float s) const {
  return Vector3f(s * x, s * y, s * z);
}

inline Vector3f& Vector3f::operator*=(const float s) {
  x *= s;
  y *= s;
  z *= s;
  return *this;
}

inline Vector3f Vector3f::operator/(const float s) const {
  return Vector3f(x / s, y / s, z / s);
}

inline Vector3f& Vector3f::operator/=(const float s) {
  x /= s;
  y /= s;
  z /= s;
  return *this;
}

inline float Vector3f::length() const {
  return std::sqrt(x * x + y * y + z * z);
}

inline float Vector3f::lengthSquared() const { return x * x + y * y + z * z; }
inline Vector3f Vector3f::normalized() const { return *this / length(); }

inline float Vector3f::dot(const Vector3f& v) const {
  return x * v.x + y * v.y + z * v.z;
}

inline Vector3f Vector3f::cross(const Vector3f& v) const {
  return Vector3f(y * v.z - v.y * z, z * v.x - v.z * x, x * v.y - v.x * y);
}

inline bool Vector3f::operator==(const Vector3f& other) const {
  return x == other.x && y == other.y && z == other.z;
}

inline bool Vector3f::operator!=(const Vector3f& other) const {
  return !(*this == other);
}

inline Vector3f operator*(const float s, const Vector3f& v) { return v * s; }

inline std::ostream& operator<<(std::ostream& os, const Vector3f& v) {
  return os << "Vector3f (" << v.x << ", " << v.y << ", " << v.z << ")";
}

} // namespace Dunjun

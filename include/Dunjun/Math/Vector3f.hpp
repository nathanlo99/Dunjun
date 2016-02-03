#pragma once
#ifndef DUNJUN_MATH_VECTOR3F_HPP
#define DUNJUN_MATH_VECTOR3F_HPP

#include <ostream>

namespace Dunjun {
struct Vector3f {
  Vector3f() : x(0), y(0), z(0) {}
  Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}
  Vector3f(float xy[3]) : x(xy[0]), y(xy[1]), z(xy[2]) {}

  inline Vector3f operator+(const Vector3f& other) const {
    return Vector3f(x + other.x, y + other.y, z + other.z);
  }

  inline Vector3f operator-(const Vector3f& other) const {
    return Vector3f(x - other.x, y - other.y, z - other.z);
  }

  inline Vector3f operator*(const Vector3f& other) const {
    return Vector3f(x * other.x, y * other.y, z * other.z);
  }

  inline Vector3f operator/(const Vector3f& other) const {
    return Vector3f(x / other.x, y / other.y, z / other.z);
  }

  inline Vector3f operator-() const { return Vector3f(-x, -y, -z); }

  inline Vector3f& operator+=(const Vector3f& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }

  inline Vector3f& operator-=(const Vector3f& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }

  inline Vector3f operator*(float s) const {
    return Vector3f(s * x, s * y, s * z);
  }

  inline Vector3f& operator*=(float s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }

  inline Vector3f operator/(float s) const {
    return Vector3f(x / s, y / s, z / s);
  }

  inline Vector3f& operator/=(float s) {
    x /= s;
    y /= s;
    z /= s;
    return *this;
  }

  inline float length() const { return sqrtf(x * x + y * y + z * z); }

  inline float lengthSquared() const { return x * x + y * y + z * z; }
  Vector3f normalize() const { return *this / length(); }

  inline float dot(const Vector3f& v) const {
    return x * v.x + y * v.y + z * v.z;
  }

  inline Vector3f cross(const Vector3f& v) const {
    return Vector3f(y * v.z - v.y * z, z * v.x - v.z * x, x * v.y - v.x * y);
  }

  inline bool operator==(const Vector3f& other) const {
    return x == other.x && y == other.y && z == other.z;
  }

  inline bool operator!=(const Vector3f& other) const {
    return !(*this == other);
  }

  inline float& operator[](int index) { return data[index]; }
  inline const float& operator[](int index) const { return data[index]; }

  union {
    float data[3];
    struct {
      float x, y, z;
    };
    struct {
      float s, t, p;
    };
  };
};

inline Vector3f operator*(float s, const Vector3f& v) { return v * s; }

inline std::ostream& operator<<(std::ostream& os, const Vector3f& v) {
  return os << "Vector3f (" << v.x << ", " << v.y << ", " << v.z << ")";
}

} // namespace Dunjun

#endif

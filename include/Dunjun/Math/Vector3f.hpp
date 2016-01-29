#pragma once
#ifndef DUNJUN_MATH_VECTOR3F_HPP
#define DUNJUN_MATH_VECTOR3F_HPP

#include <cmath>
#include <Dunjun/Math/Vector2f.hpp>

namespace Dunjun {
struct Vector3f {
  Vector3f() : x(0), y(0), z(0) {}
  Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}
  Vector3f(float xy[3]) : x(xy[0]), y(xy[1]), z(xy[2]) {}
  explicit Vector3f(float a) : x(a), y(a), z(a) {}

  inline Vector3f operator+(const Vector3f& other) const {
    return Vector3f(x + other.x, y + other.y, z + other.z);
  }

  inline Vector3f operator-(const Vector3f& other) const {
    return Vector3f(x - other.x, y - other.y, z - other.z);
  }

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

  inline Vector3f operator*(const float s) const {
    return Vector3f(s * x, s * y, s * z);
  }

  inline Vector3f& operator*=(const float s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }

  inline Vector3f operator/(const float s) const {
    return Vector3f(x / s, y / s, z / s);
  }

  inline Vector3f& operator/=(const float s) {
    x /= s;
    y /= s;
    z /= s;
    return *this;
  }

  inline float length() const { return std::sqrt(x * x + y * y + z * z); }
  inline float lengthSquared() const { return x * x + y * y + z * z; }
  inline Vector3f normalized() const { return *this / length(); }
  // inline Vector3f& normalize() { return (*this) /= length(); }

  inline float dot(const Vector3f& v) const {
    return x * v.x + y * v.y + z * v.z;
  }

  inline Vector3f cross(const Vector3f& v) const {
    return Vector3f(y * v.z - v.y * z, z * v.x - v.z * x, x * v.y - v.x * y);
  }

  union {
    float data[3];
    struct {
      float x, y, z;
    };
    struct {
      float s, t, p;
    };
  };

  inline float& operator[](std::size_t index) { return data[index]; }
  inline const float& operator[](std::size_t index) const {
    return data[index];
  }
};

inline Vector3f operator*(const float s, const Vector3f& v) { return v * s; }

} // namespace Dunjun

#endif

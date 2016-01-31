#pragma once
#ifndef DUNJUN_MATH_VECTOR4F_HPP
#define DUNJUN_MATH_VECTOR4F_HPP

#include <ostream>

namespace Dunjun {
struct Vector4f {
  Vector4f() : x(0), y(0), z(0), w(0) {}
  Vector4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
  Vector4f(float xy[4]) : x(xy[0]), y(xy[1]), z(xy[2]), w(xy[3]) {}

  inline Vector4f operator+(const Vector4f& other) const {
    return Vector4f(x + other.x, y + other.y, z + other.z, w + other.w);
  }

  inline Vector4f operator-(const Vector4f& other) const {
    return Vector4f(x - other.x, y - other.y, z - other.z, w - other.w);
  }

  inline Vector4f& operator+=(const Vector4f& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
  }

  inline Vector4f& operator-=(const Vector4f& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
  }

  inline Vector4f operator*(float s) const {
    return Vector4f(s * x, s * y, s * z, s * w);
  }

  inline Vector4f& operator*=(float s) {
    x *= s;
    y *= s;
    z *= s;
    w *= s;
    return *this;
  }

  inline Vector4f operator/(float s) const {
    return Vector4f(x / s, y / s, z / s, w / s);
  }

  inline Vector4f& operator/=(float s) {
    x /= s;
    y /= s;
    z /= s;
    w /= s;
    return *this;
  }

  inline float length() const { return sqrtf(x * x + y * y + z * z + w * w); }

  inline float lengthSquared() const { return x * x + y * y + z * z + w * w; }

  inline Vector4f normalize() const { return *this / length(); }

  inline float dot(const Vector4f& v) const {
    return x * v.x + y * v.y + z * v.z + w * v.w;
  }

  inline bool operator==(const Vector4f& other) const {
    return x == other.x && y == other.y && other.z == z && other.w == w;
  }

  inline bool operator!=(const Vector4f& other) const {
    return !(*this == other);
  }

  inline float& operator[](int index) { return data[index]; }
  inline const float& operator[](int index) const { return data[index]; }

  union {
    float data[4];
    struct {
      float x, y, z, w;
    };
    struct {
      float r, g, b, a;
    };
    struct {
      float s, t, p, q;
    };
  };
};

inline Vector4f operator*(float s, const Vector4f& v) { return v * s; }

inline std::ostream& operator<<(std::ostream& os, const Vector4f& v) {
  return os << "Vector4f(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w
            << ")";
}

} // namespace Dunjun

#endif

#pragma once
#ifndef DUNJUN_MATH_VECTOR4F_HPP
#define DUNJUN_MATH_VECTOR4F_HPP

#include <ostream>

namespace Dunjun {
struct Vector4f {
  Vector4f();
  Vector4f(float x, float y, float z, float w);
  Vector4f(float xy[4]);
  explicit Vector4f(float a);
  Vector4f(const Vector4f& other) = default;

  Vector4f operator+(const Vector4f& other) const;
  Vector4f operator-(const Vector4f& other) const;
  Vector4f& operator+=(const Vector4f& other);
  Vector4f& operator-=(const Vector4f& other);
  Vector4f operator*(const float s) const;
  Vector4f& operator*=(const float s);
  Vector4f operator/(const float s) const;
  Vector4f& operator/=(const float s);

  float length() const;
  float lengthSquared() const;
  Vector4f normalized() const;
  float dot(const Vector4f& v) const;

  bool operator==(const Vector4f& other) const;
  bool operator!=(const Vector4f& other) const;

  float& operator[](int index) { return data[index]; }
  const float& operator[](int index) const { return data[index]; }

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

Vector4f operator*(const float s, const Vector4f& v);
std::ostream& operator<<(std::ostream& os, const Vector4f& v);

} // namespace Dunjun

#endif

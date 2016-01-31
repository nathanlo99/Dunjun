#pragma once
#ifndef DUNJUN_MATH_VECTOR2F_HPP
#define DUNJUN_MATH_VECTOR2F_HPP

#include <ostream>

namespace Dunjun {
struct Vector2f {
  Vector2f();
  Vector2f(float x, float y);
  Vector2f(float xy[2]);

  Vector2f operator+(const Vector2f& other) const;
  Vector2f operator-(const Vector2f& other) const;
  Vector2f& operator+=(const Vector2f& other);
  Vector2f& operator-=(const Vector2f& other);
  Vector2f operator*(float s) const;
  Vector2f& operator*=(float s);
  Vector2f operator/(float s) const;
  Vector2f& operator/=(float s);

  float length() const;
  float lengthSquared() const;
  Vector2f normalize() const;
  float dot(const Vector2f& v) const;
  float cross(const Vector2f& v) const;

  bool operator==(const Vector2f& other) const;
  bool operator!=(const Vector2f& other) const;

  inline float& operator[](int index) { return data[index]; }
  inline const float& operator[](int index) const { return data[index]; }

  union {
    float data[2];
    struct {
      float x, y;
    };
    struct {
      float s, t;
    };
  };
};

Vector2f operator*(float s, const Vector2f& v);
std::ostream& operator<<(std::ostream& os, const Vector2f& v);

} // namespace Dunjun

#endif

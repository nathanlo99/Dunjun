#pragma once
#ifndef DUNJUN_MATH_VECTOR3F_HPP
#define DUNJUN_MATH_VECTOR3F_HPP

#include <ostream>

namespace Dunjun {
struct Vector3f {
  Vector3f();
  Vector3f(const float x, const float y, const float z);
  Vector3f(const float xy[3]);

  Vector3f operator+(const Vector3f& other) const;
  Vector3f operator-(const Vector3f& other) const;
  Vector3f& operator+=(const Vector3f& other);
  Vector3f& operator-=(const Vector3f& other);
  Vector3f operator*(const float s) const;
  Vector3f& operator*=(const float s);
  Vector3f operator/(const float s) const;
  Vector3f& operator/=(const float s);

  float length() const;
  float lengthSquared() const;
  Vector3f normalize() const;
  float dot(const Vector3f& v) const;
  Vector3f cross(const Vector3f& v) const;

  bool operator==(const Vector3f& other) const;
  bool operator!=(const Vector3f& other) const;

  inline float& operator[](const int index) { return data[index]; }
  inline const float& operator[](const int index) const { return data[index]; }

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

Vector3f operator*(const float s, const Vector3f& v);
std::ostream& operator<<(std::ostream& os, const Vector3f& v);

} // namespace Dunjun

#endif

#pragma once
#ifndef DUNJUN_MATH_VECTOR4F_HPP
#define DUNJUN_MATH_VECTOR4F_HPP

namespace Dunjun {
struct Vector4f {
  Vector4f();
  Vector4f(float x, float y, float z, float w);
  Vector4f(float xy[4]);
  explicit Vector4f(float a);

  inline Vector4f operator+(const Vector4f& other) const;
  inline Vector4f operator-(const Vector4f& other) const;
  inline Vector4f& operator+=(const Vector4f& other);
  inline Vector4f& operator-=(const Vector4f& other);
  inline Vector4f operator*(const float s) const;
  inline Vector4f& operator*=(const float s);
  inline Vector4f operator/(const float s) const;
  inline Vector4f& operator/=(const float s);

  inline float length() const;
  inline float lengthSquared() const;
  inline Vector4f normalized() const;
  inline float dot(const Vector4f& v) const;

  inline bool operator==(const Vector4f& other) const;
  inline bool operator!=(const Vector4f& other) const;

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

inline Vector4f operator*(const float s, const Vector4f& v);
inline std::ostream& operator<<(std::ostream& os, const Vector4f& v);

} // namespace Dunjun

#endif

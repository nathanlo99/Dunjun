#pragma once
#ifndef DUNJUN_MATH_VECTOR3F_HPP
#define DUNJUN_MATH_VECTOR3F_HPP

namespace Dunjun {
struct Vector3f {
  Vector3f();
  Vector3f(float x, float y, float z);
  Vector3f(float xy[3]);
  explicit Vector3f(float a);

  inline Vector3f operator+(const Vector3f& other) const;
  inline Vector3f operator-(const Vector3f& other) const;
  inline Vector3f& operator+=(const Vector3f& other);
  inline Vector3f& operator-=(const Vector3f& other);
  inline Vector3f operator*(const float s) const;
  inline Vector3f& operator*=(const float s);
  inline Vector3f operator/(const float s) const;
  inline Vector3f& operator/=(const float s);

  inline float length() const;
  inline float lengthSquared() const;
  inline Vector3f normalized() const;
  inline float dot(const Vector3f& v) const;
  inline Vector3f cross(const Vector3f& v) const;

  inline bool operator==(const Vector3f& other) const;
  inline bool operator!=(const Vector3f& other) const;

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

inline Vector3f operator*(const float s, const Vector3f& v);
inline std::ostream& operator<<(std::ostream& os, const Vector3f& v);

} // namespace Dunjun

#endif

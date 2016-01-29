#pragma once
#ifndef DUNJUN_MATH_VECTOR2F_HPP
#define DUNJUN_MATH_VECTOR2F_HPP

namespace Dunjun {
struct Vector2f {
  Vector2f();
  explicit Vector2f(float a);
  Vector2f(float x, float y);
  Vector2f(float xy[2]);

  inline Vector2f operator+(const Vector2f& other) const;
  inline Vector2f operator-(const Vector2f& other) const;
  inline Vector2f& operator+=(const Vector2f& other);
  inline Vector2f& operator-=(const Vector2f& other);
  inline Vector2f operator*(const float s) const;
  inline Vector2f& operator*=(const float s);
  inline Vector2f operator/(const float s) const;
  inline Vector2f& operator/=(const float s);

  inline float length();
  inline float lengthSquared();
  inline Vector2f normalized();
  inline float dot(const Vector2f& v) const;
  inline float cross(const Vector2f& v) const;

  inline bool operator==(const Vector2f& other) const;
  inline bool operator!=(const Vector2f& other) const;

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

inline Vector2f operator*(const float s, const Vector2f& v);
inline std::ostream& operator<<(std::ostream& os, const Vector2f& v);

} // namespace Dunjun

#endif

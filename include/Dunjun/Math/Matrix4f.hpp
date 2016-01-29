#ifndef DUNJUN_MATH_MATRIX_HPP
#define DUNJUN_MATH_MATRIX_HPP

#include <ostream>
#include <Dunjun/Math/Vector4f.hpp>

namespace Dunjun {
class Matrix4f {
  public:
  Matrix4f();
  Matrix4f(float x);
  Matrix4f(const Vector4f& v0, const Vector4f& v1, const Vector4f& v2,
           const Vector4f& v3);

  inline Matrix4f operator+(const Matrix4f& other) const;
  inline Matrix4f operator-(const Matrix4f& other) const;
  inline Matrix4f operator*(float s) const;
  inline Matrix4f operator/(float s) const;
  inline Matrix4f& operator+=(const Matrix4f& other);
  inline Matrix4f& operator-=(const Matrix4f& other);
  inline Matrix4f& operator*=(const Matrix4f& other);
  inline Matrix4f operator*(const Matrix4f& other) const;
  inline Vector4f operator*(const Vector4f& v) const;
  inline Matrix4f transpose() const;
  inline float determinant() const;
  inline Matrix4f inverse() const;

  inline bool operator==(const Matrix4f& other);
  inline bool operator!=(const Matrix4f& other);

  inline Vector4f& operator[](int index) { return m[index]; }
  inline const Vector4f& operator[](int index) const { return m[index]; }

  private:
  Vector4f m[4];
};

} // namespace Dunjun

#endif

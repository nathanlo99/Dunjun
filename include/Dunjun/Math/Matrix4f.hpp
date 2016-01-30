#pragma once
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
  Matrix4f(const Matrix4f& other) = default;

  Matrix4f operator+(const Matrix4f& other) const;
  Matrix4f operator-(const Matrix4f& other) const;
  Matrix4f operator*(float s) const;
  Matrix4f operator/(float s) const;
  Matrix4f& operator+=(const Matrix4f& other);
  Matrix4f& operator-=(const Matrix4f& other);
  Matrix4f& operator*=(const Matrix4f& other);
  Matrix4f operator*(const Matrix4f& other) const;
  Vector4f operator*(const Vector4f& v) const;
  Matrix4f transpose() const;
  float determinant() const;
  Matrix4f inverse() const;

  bool operator==(const Matrix4f& other);
  bool operator!=(const Matrix4f& other);

  Vector4f& operator[](int index) { return m[index]; }
  const Vector4f& operator[](int index) const { return m[index]; }

  private:
  Vector4f m[4];
};

Matrix4f operator*(float s, const Matrix4f& m);
std::ostream& operator<<(std::ostream& os, const Matrix4f& m);

} // namespace Dunjun

#endif

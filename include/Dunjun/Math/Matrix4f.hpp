#ifndef DUNJUN_MATH_MATRIX_HPP
#define DUNJUN_MATH_MATRIX_HPP

#include <ostream>
#include <Dunjun/Math/Vector4f.hpp>

namespace Dunjun {
class Matrix4f {
  public:
  Matrix4f() : m({{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}) {}
  Matrix4f(float x)
  : m({{x, 0, 0, 0}, {0, x, 0, 0}, {0, 0, x, 0}, {0, 0, 0, x}}) {}
  Matrix4f(const Vector4f& v0, const Vector4f& v1, const Vector4f& v2,
           const Vector4f& v3)
  : m({v0, v1, v2, v3}) {}

  inline Matrix4f operator+(const Matrix4f& other) const {
    return Matrix4f(m[0] + other[0], m[1] + other[1], m[2] + other[2],
                    m[3] + other[3]);
  }

  inline Matrix4f operator-(const Matrix4f& other) const {
    return Matrix4f(m[0] - other[0], m[1] - other[1], m[2] - other[2],
                    m[3] - other[3]);
  }

  inline Matrix4f operator*(float s) const {
    return Matrix4f(m[0] * s, m[1] * s, m[2] * s, m[3] * s);
  }

  inline Matrix4f operator/(float s) const {
    return Matrix4f(m[0] / s, m[1] / s, m[2] / s, m[3] / s);
  }

  inline Matrix4f& operator+=(const Matrix4f& other) {
    return (*this = (*this) + other);
  }

  inline Matrix4f& operator-=(const Matrix4f& other) {
    return (*this = (*this) - other);
  }

  inline Matrix4f& operator*=(const Matrix4f& other) {
    return (*this = (*this) * other);
  }

  inline Matrix4f operator*(const Matrix4f& other) const {
    Matrix4f result;
    result[0] = m[0] * other[0][0] + m[1] * other[0][1] + m[2] * other[0][2] +
                m[3] * other[0][3];
    result[1] = m[0] * other[1][0] + m[1] * other[1][1] + m[2] * other[1][2] +
                m[3] * other[1][3];
    result[2] = m[0] * other[2][0] + m[1] * other[2][1] + m[2] * other[2][2] +
                m[3] * other[2][3];
    result[3] = m[0] * other[3][0] + m[1] * other[3][1] + m[2] * other[3][2] +
                m[3] * other[3][3];
    return result;
  }

  inline Vector4f operator*(const Vector4f& v) const {
    return m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3] * v[3];
  }

  inline Matrix4f transpose() {
    Matrix4f res;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) { res[i][j] = m[j][i]; }
    }
    return res;
  }

  inline float determinant() const {
    return m[0][3] * m[1][2] * m[2][1] * m[3][0] -
           m[0][2] * m[1][3] * m[2][1] * m[3][0] -
           m[0][3] * m[1][1] * m[2][2] * m[3][0] +
           m[0][1] * m[1][3] * m[2][2] * m[3][0] +
           m[0][2] * m[1][1] * m[2][3] * m[3][0] -
           m[0][1] * m[1][2] * m[2][3] * m[3][0] -
           m[0][3] * m[1][2] * m[2][0] * m[3][1] +
           m[0][2] * m[1][3] * m[2][0] * m[3][1] +
           m[0][3] * m[1][0] * m[2][2] * m[3][1] -
           m[0][0] * m[1][3] * m[2][2] * m[3][1] -
           m[0][2] * m[1][0] * m[2][3] * m[3][1] +
           m[0][0] * m[1][2] * m[2][3] * m[3][1] +
           m[0][3] * m[1][1] * m[2][0] * m[3][2] -
           m[0][1] * m[1][3] * m[2][0] * m[3][2] -
           m[0][3] * m[1][0] * m[2][1] * m[3][2] +
           m[0][0] * m[1][3] * m[2][1] * m[3][2] +
           m[0][1] * m[1][0] * m[2][3] * m[3][2] -
           m[0][0] * m[1][1] * m[2][3] * m[3][2] -
           m[0][2] * m[1][1] * m[2][0] * m[3][3] +
           m[0][1] * m[1][2] * m[2][0] * m[3][3] +
           m[0][2] * m[1][0] * m[2][1] * m[3][3] -
           m[0][0] * m[1][2] * m[2][1] * m[3][3] -
           m[0][1] * m[1][0] * m[2][2] * m[3][3] +
           m[0][0] * m[1][1] * m[2][2] * m[3][3];
  }

  Matrix4f inverse() const {
    Matrix4f inv;

    inv[0][0] = m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] -
                m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] +
                m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];

    inv[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] +
                m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] -
                m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];

    inv[2][0] = m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] -
                m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] +
                m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];

    inv[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] +
                m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] -
                m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

    inv[0][1] = -m[0][1] * m[2][2] * m[3][3] + m[0][1] * m[2][3] * m[3][2] +
                m[2][1] * m[0][2] * m[3][3] - m[2][1] * m[0][3] * m[3][2] -
                m[3][1] * m[0][2] * m[2][3] + m[3][1] * m[0][3] * m[2][2];

    inv[1][1] = m[0][0] * m[2][2] * m[3][3] - m[0][0] * m[2][3] * m[3][2] -
                m[2][0] * m[0][2] * m[3][3] + m[2][0] * m[0][3] * m[3][2] +
                m[3][0] * m[0][2] * m[2][3] - m[3][0] * m[0][3] * m[2][2];

    inv[2][1] = -m[0][0] * m[2][1] * m[3][3] + m[0][0] * m[2][3] * m[3][1] +
                m[2][0] * m[0][1] * m[3][3] - m[2][0] * m[0][3] * m[3][1] -
                m[3][0] * m[0][1] * m[2][3] + m[3][0] * m[0][3] * m[2][1];

    inv[3][1] = m[0][0] * m[2][1] * m[3][2] - m[0][0] * m[2][2] * m[3][1] -
                m[2][0] * m[0][1] * m[3][2] + m[2][0] * m[0][2] * m[3][1] +
                m[3][0] * m[0][1] * m[2][2] - m[3][0] * m[0][2] * m[2][1];

    inv[0][2] = m[0][1] * m[1][2] * m[3][3] - m[0][1] * m[1][3] * m[3][2] -
                m[1][1] * m[0][2] * m[3][3] + m[1][1] * m[0][3] * m[3][2] +
                m[3][1] * m[0][2] * m[1][3] - m[3][1] * m[0][3] * m[1][2];

    inv[1][2] = -m[0][0] * m[1][2] * m[3][3] + m[0][0] * m[1][3] * m[3][2] +
                m[1][0] * m[0][2] * m[3][3] - m[1][0] * m[0][3] * m[3][2] -
                m[3][0] * m[0][2] * m[1][3] + m[3][0] * m[0][3] * m[1][2];

    inv[2][2] = m[0][0] * m[1][1] * m[3][3] - m[0][0] * m[1][3] * m[3][1] -
                m[1][0] * m[0][1] * m[3][3] + m[1][0] * m[0][3] * m[3][1] +
                m[3][0] * m[0][1] * m[1][3] - m[3][0] * m[0][3] * m[1][1];

    inv[3][2] = -m[0][0] * m[1][1] * m[3][2] + m[0][0] * m[1][2] * m[3][1] +
                m[1][0] * m[0][1] * m[3][2] - m[1][0] * m[0][2] * m[3][1] -
                m[3][0] * m[0][1] * m[1][2] + m[3][0] * m[0][2] * m[1][1];

    inv[0][3] = -m[0][1] * m[1][2] * m[2][3] + m[0][1] * m[1][3] * m[2][2] +
                m[1][1] * m[0][2] * m[2][3] - m[1][1] * m[0][3] * m[2][2] -
                m[2][1] * m[0][2] * m[1][3] + m[2][1] * m[0][3] * m[1][2];

    inv[1][3] = m[0][0] * m[1][2] * m[2][3] - m[0][0] * m[1][3] * m[2][2] -
                m[1][0] * m[0][2] * m[2][3] + m[1][0] * m[0][3] * m[2][2] +
                m[2][0] * m[0][2] * m[1][3] - m[2][0] * m[0][3] * m[1][2];

    inv[2][3] = -m[0][0] * m[1][1] * m[2][3] + m[0][0] * m[1][3] * m[2][1] +
                m[1][0] * m[0][1] * m[2][3] - m[1][0] * m[0][3] * m[2][1] -
                m[2][0] * m[0][1] * m[1][3] + m[2][0] * m[0][3] * m[1][1];

    inv[3][3] = m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1] -
                m[1][0] * m[0][1] * m[2][2] + m[1][0] * m[0][2] * m[2][1] +
                m[2][0] * m[0][1] * m[1][2] - m[2][0] * m[0][2] * m[1][1];

    float det = m[0][0] * inv[0][0] + m[0][1] * inv[1][0] +
                m[0][2] * inv[2][0] + m[0][3] * inv[3][0];

    return inv / det;
  }

  inline Vector4f& operator[](std::size_t index) { return m[index]; }
  inline const Vector4f& operator[](std::size_t index) const {
    return m[index];
  }

  inline bool operator==(const Matrix4f& other) {
    if (m[0] != other[0]) return false;
    if (m[1] != other[1]) return false;
    if (m[2] != other[2]) return false;
    if (m[3] != other[3]) return false;
    return true;
  }
  inline bool operator!=(const Matrix4f& other) { return !(*this == other); }

  private:
  Vector4f m[4];
};

inline Matrix4f operator*(float s, const Matrix4f& m) { return m * s; }

inline std::ostream& operator<<(std::ostream& os, const Matrix4f& m) {
  return os << "Matrix4f("
            << "\n " << m[0] << ",\n " << m[1] << ",\n " << m[2] << ",\n "
            << m[3] << ")";
}
} // namespace Dunjun

#endif

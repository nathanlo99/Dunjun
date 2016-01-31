#pragma once
#ifndef DUNJUN_MATH_QUATERNION_HPP
#define DUNJUN_MATH_QUATERNION_HPP

#include <cmath>
#include <ostream>

#include <Dunjun/common.hpp>
#include <Dunjun/Math/Vector3f.hpp>
#include <Dunjun/Math/Matrix4f.hpp>

namespace Dunjun {

struct EulerAngles {
  float pitch, yaw, roll;
};

struct Quaternion {
  Quaternion() : x(0), y(0), z(0), w(1) {}
  Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
  Quaternion(const Vector3f& v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}

  Quaternion(float angle, bool degrees, const Vector3f& axis) {
    if (degrees) angle *= M_PI / 180;

    const Vector3f a = axis.normalize();
    const float sine = sinf(0.5f * angle);

    x = a.x * sine;
    y = a.y * sine;
    z = a.z * sine;
    w = cosf(0.5f * angle);
  }

  inline Quaternion operator+(const Quaternion& other) const {
    return Quaternion(x + other.x, y + other.y, z + other.z, w + other.w);
  }

  inline Quaternion operator-(const Quaternion& other) const {
    return Quaternion(x - other.x, y - other.y, z - other.z, w - other.w);
  }

  inline Quaternion operator*(float s) const {
    return Quaternion(x * s, y * s, z * s, w * s);
  }

  inline Quaternion operator/(float s) const {
    return Quaternion(x / s, y / s, z / s, w / s);
  }

  Quaternion operator*(const Quaternion& b) const {
    float xx = w * b.x + x * b.w + y * b.z - z * b.y;
    float yy = w * b.y - x * b.z + y * b.w + z * b.x;
    float zz = w * b.z + x * b.y - y * b.x + z * b.w;
    float ww = w * b.w - x * b.x - y * b.y - z * b.z;
    return Quaternion(xx, yy, zz, ww);
  }

  inline Vector3f operator*(const Vector3f& v) {
    const Vector3f xyz(x, y, z);
    Vector3f t = 2.0f * xyz.cross(v);
    return v + w * t + xyz.cross(t);
  }

  inline float dot(const Quaternion& other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
  }

  inline Quaternion cross(const Quaternion& b) const {
    return Quaternion(w * b.x + x * b.w + y * b.z - z * b.y,
                      w * b.y + y * b.w + z * b.x - x * b.z,
                      w * b.z + z * b.w + x * b.y - y * b.x,
                      w * b.w - x * b.x - y * b.y - z * b.z);
  }

  inline Quaternion conjugate() const { return Quaternion(-x, -y, -z, w); }
  inline Quaternion inverse() const { return conjugate() / lengthSquared(); }
  inline float lengthSquared() const { return x * x + y * y + z * z + w * w; }
  inline float length() const { return sqrtf(x * x + y * y + z * z + w * w); }
  inline Quaternion normalize() const { return (*this) / length(); }

  inline float angle() const { return 2.0f * acosf(w); }

  inline EulerAngles getEulerAngles() const {
    EulerAngles e;
    e.pitch = atan2f(2.0f * y * z + w * x, w * w - x * x - y * y + z * z);
    e.roll  = atan2f(2.0f * x * y + z * w, x * x + w * w - y * y - z * z);
    e.yaw   = asinf(-2.0f * (x * z - w * y));
    return e;
  }

  inline Matrix4f toMatrix() {
    Matrix4f mat;
    const Quaternion a = normalize();

    const float xx = a.x * a.x;
    const float yy = a.y * a.y;
    const float zz = a.z * a.z;
    const float xy = a.x * a.y;
    const float xz = a.x * a.z;
    const float yz = a.y * a.z;
    const float wx = a.w * a.x;
    const float wy = a.w * a.y;
    const float wz = a.w * a.z;

    mat[0][0] = 1.0f - 2.0f * (yy + zz);
    mat[0][1] = 2.0f * (xy + wz);
    mat[0][2] = 2.0f * (xz - wy);

    mat[1][0] = 2.0f * (xy - wz);
    mat[1][1] = 1.0f - 2.0f * (xx + zz);
    mat[1][2] = 2.0f * (yz + wx);

    mat[2][0] = 2.0f * (xz + wy);
    mat[2][1] = 2.0f * (yz - wx);
    mat[2][2] = 1.0f - 2.0f * (xx + yy);

    mat[3][3] = 1.0f;
    return mat;
  }

  inline Vector3f axis() const {
    if (1.0f <= w * w) return Vector3f(0, 0, 1);
    return Vector3f(x, y, z) / sqrtf(1.0f - w * w);
  }

  inline bool operator==(const Quaternion& other) const {
    return x == other.x && y == other.y && z == other.z && w == other.w;
  }

  inline bool operator!=(const Quaternion& other) const {
    return !(*this == other);
  }

  float x, y, z, w;
};

inline Quaternion operator*(float s, const Quaternion& q) { return q * s; }
inline std::ostream& operator<<(std::ostream& os, const Quaternion& q) {
  return os << "Quaternion (" << q.x << ", " << q.y << ", " << q.z << ", "
            << q.w << ")";
}

// INTERPOLATION FUNCTIONS
inline float lerp(float x, float y, float t) { return x * (1.0f - t) + y * t; }

inline Quaternion slerp(const Quaternion& x, const Quaternion& y, float t) {
  Quaternion z   = y;
  float cosTheta = x.dot(y);
  if (cosTheta < 0.0f) {
    z = y * -1;
    cosTheta *= -1;
  } else if (cosTheta > 1.0f) {
    return Quaternion(lerp(x.x, y.x, t), lerp(x.y, y.y, t), lerp(x.z, y.z, t),
                      lerp(x.w, y.w, t));
  } else {
    float angle = acosf(cosTheta);
    return (sinf(1.0f - t * angle) * x + sinf(t * angle) * z) / sinf(angle);
  }
}

} // namespace Dunjun

#endif

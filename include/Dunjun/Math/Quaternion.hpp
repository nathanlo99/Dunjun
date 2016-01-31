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
    const Vector3f a_xyz(x, y, z);
    const Vector3f b_xyz(b.x, b.y, b.z);
    Vector3f c_xyz;
    float c_w;
    c_xyz = w * b_xyz + b.w * a_xyz + a_xyz.cross(b_xyz);
    c_w = w * b.w - a_xyz.dot(b_xyz);
    return Quaternion(c_xyz, c_w);
  }

  inline Vector3f operator*(const Vector3f& v) {
    const Vector3f xyz(x, y, z);
    Vector3f t = 2.0f * xyz.cross(v);
    return v + w * t + xyz.cross(t);
  }

  inline float dot(const Quaternion& other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
  }

  inline Quaternion conjugate() const { return Quaternion(-x, -y, -z, w); }
  inline Quaternion inverse() const { return conjugate() / lengthSquared(); }
  inline float lengthSquared() const { return x * x + y * y + z * z + w * w; }
  inline float length() const { return sqrtf(x * x + y * y + z * z + w * w); }
  inline Quaternion normalize() const { return (*this) / length(); }

  inline float angle() const { return 2.0f * acosf(w); }

  inline EulerAngles getEulerAngles() const {
    EulerAngles e;
    e.roll  = atan2f(2.0f * x * y + z * w, x * x + w * w - y * y - z * z);
    e.pitch = atan2f(2.0f * y * z + w * x, w * w - x * x - y * y + z * z);
    e.yaw   = asinf(-2.0f * (x * z - w * y));
    return e;
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

} // namespace Dunjun

#endif

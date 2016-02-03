#pragma once
#ifndef DUNJUN_MATH_TRANSFORM_HPP
#define DUNJUN_MATH_TRANSFORM_HPP

#include <cmath>

#include <Dunjun/Math/Vector3f.hpp>
#include <Dunjun/Math/Matrix4f.hpp>
#include <Dunjun/Math/Quaternion.hpp>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

namespace Dunjun {

inline Matrix4f identityMatrix() {
  Matrix4f m;
  m[0][0] = 1;
  m[1][1] = 1;
  m[2][2] = 1;
  m[3][3] = 1;
  return m;
}

inline Matrix4f translateMatrix(const Vector3f& v) {
  Matrix4f m;
  m[0][0] = 1.0f;
  m[1][1] = 1.0f;
  m[2][2] = 1.0f;
  m[3]    = Vector4f(v[0], v[1], v[2], 1);
  return m;
}

inline Matrix4f rotateMatrix(float angle, bool degrees, const Vector3f& v) {

  if (degrees) angle *= M_PI / 180;

  float c = cosf(angle);
  float s = sinf(angle);

  const Vector3f axis = v.normalize();
  const Vector3f t    = (1.0f - c) * axis;

  Matrix4f rot;
  rot[0][0] = c + t[0] * axis[0];
  rot[0][1] = 0 + t[0] * axis[1] + s * axis[2];
  rot[0][2] = 0 + t[0] * axis[2] - s * axis[1];
  rot[0][3] = 0;

  rot[1][0] = 0 + t[1] * axis[0] - s * axis[2];
  rot[1][1] = c + t[1] * axis[1];
  rot[1][2] = 0 + t[1] * axis[2] + s * axis[0];
  rot[1][3] = 0;

  rot[2][0] = 0 + t[2] * axis[0] + s * axis[1];
  rot[2][1] = 0 + t[2] * axis[1] - s * axis[0];
  rot[2][2] = c + t[2] * axis[2];
  rot[2][3] = 0;

  return rot;
}

inline Matrix4f scaleMatrix(const Vector3f& v) {
  Matrix4f result;
  result[0][0] = v[0];
  result[1][1] = v[1];
  result[2][2] = v[2];
  result[3][3] = 1.0f;
  return result;
}

inline Matrix4f ortho(float left, float right, float bottom, float top) {
  Matrix4f result;
  result[0][0] = 2.0f / (right - left);
  result[1][1] = 2.0f / (top - bottom);
  result[2][2] = -1.0f;
  result[3][0] = (left + right) / (left - right);
  result[3][1] = (bottom + top) / (bottom - top);
  result[3][3] = 1.0f;
  return result;
}

inline Matrix4f ortho(float left, float right, float bottom, float top,
                      float zNear, float zFar) {
  Matrix4f result;
  result[0][0] = 2.0f / (right - left);
  result[1][1] = 2.0f / (top - bottom);
  result[2][2] = 2.0f / (zNear - zFar);
  result[3][0] = (left + right) / (left - right);
  result[3][1] = (bottom + top) / (bottom - top);
  result[3][2] = (zFar + zNear) / (zNear - zFar);
  result[3][3] = 1.0f;
  return result;
}

inline Matrix4f perspective(float fov, bool degrees, float aspect, float zNear,
                            float zFar) {
  if (degrees) fov *= M_PI / 180;
  float tanHalfFOV = tanf(fov / 2.0f);

  Matrix4f result;
  result[0][0] = 1.0f / (aspect * tanHalfFOV);
  result[1][1] = 1.0f / (tanHalfFOV);
  result[2][2] = -(zFar + zNear) / (zFar - zNear);
  result[2][3] = -1.0f;
  result[3][2] = 2.0f * zFar * zNear / (zNear - zFar);

  return result;
}

inline Matrix4f perspective(float fov, bool degrees, float aspect,
                            float zNear) {
  if (degrees) fov *= M_PI / 180;
  float tanHalfFOV = tanf(fov / 2.0f);

  Matrix4f result;
  result[0][0] = 1.0f / (tanHalfFOV * aspect);
  result[1][1] = 1.0f / tanHalfFOV;
  result[2][2] = -1.0f;
  result[2][3] = -1.0f;
  result[3][2] = -2.0f * zNear;
  return result;
}

inline Matrix4f m_lookAt(const Vector3f& eye, const Vector3f& center,
                         const Vector3f& up) {

  const Vector3f f = (center - eye).normalize();
  const Vector3f s = f.cross(up).normalize();
  const Vector3f u = s.cross(f);

  Matrix4f result;

  result[0][0] = s.x;
  result[1][0] = s.y;
  result[2][0] = s.z;

  result[0][1] = u.x;
  result[1][1] = u.y;
  result[2][1] = u.z;

  result[0][2] = -f.x;
  result[1][2] = -f.y;
  result[2][2] = -f.z;

  result[3][0] = -eye.dot(s);
  result[3][1] = -eye.dot(u);
  result[3][2] = eye.dot(f);
  result[3][3] = 1;

  return result;
}

struct Transform {

  inline Transform operator*(const Transform& other) const {
    Transform result;
    result.position = position + rotation * (scale * other.position);
    result.rotation = rotation * other.rotation;
    result.scale    = scale * (rotation * other.scale);
    return result;
  }

  inline Transform operator/(const Transform& other) const {
    Transform result;
    const Quaternion conj = other.rotation.inverse();

    result.position = (conj * (position - other.position)) / other.scale;
    result.rotation = conj * rotation;
    result.scale    = conj * (scale / other.scale);
    return result;
  }

  inline Transform inverse() const { return Transform() / *this; }

  inline Matrix4f toMatrix() {
    return translateMatrix(position) * rotation.toMatrix() * scaleMatrix(scale);
  }

  Vector3f position   = {0, 0, 0};
  Quaternion rotation = {0, 0, 0, 1};
  Vector3f scale      = {1, 1, 1};
};

inline Quaternion toQuaternion(const Matrix4f& m) {
  Quaternion q;
  float m00 = m[0][0];
  float m11 = m[1][1];
  float m22 = m[2][2];

  q.w = sqrtf(MAX(0, 1 + m00 + m11 + m22)) / 2;
  q.x = sqrtf(MAX(0, 1 + m00 - m11 - m22)) / 2;
  q.y = sqrtf(MAX(0, 1 - m00 + m11 - m22)) / 2;
  q.z = sqrtf(MAX(0, 1 - m00 - m11 + m22)) / 2;
  q.x = copysign(q.x, m[1][2] - m[2][1]);
  q.y = copysign(q.y, m[2][0] - m[0][2]);
  q.z = copysign(q.z, m[0][1] - m[1][0]);
  return q;
}

} // namespace Dunjun

#endif

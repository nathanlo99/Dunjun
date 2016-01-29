#include <cmath>

#include <Dunjun/Math/Vector3f.hpp>
#include <Dunjun/Math/Matrix4f.hpp>
#include <Dunjun/Math/Transform.hpp>

namespace Dunjun {

Matrix4f translate(const Vector3f& v) {
  Matrix4f m;
  m[3] = Vector4f(v[0], v[1], v[2], 1);
  return m;
}

Matrix4f rotate(float angle, const Vector3f& v) {
  const float c = cosf(angle);
  const float s = sinf(angle);

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

Matrix4f scale(const Vector3f& v) {
  Matrix4f result;
  result[0][0] = v[0];
  result[1][1] = v[1];
  result[2][2] = v[2];
  return result;
}

} // namespace Dunjun

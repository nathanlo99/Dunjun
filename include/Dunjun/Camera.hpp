#ifndef DUNJUN_CAMERA_HPP
#define DUNJUN_CAMERA_HPP

#include <Dunjun/Math/Transform.hpp>
#include <Dunjun/Math/Vector3f.hpp>
#include <Dunjun/Math/Matrix4f.hpp>

namespace Dunjun {

struct Camera {

  inline void lookAt(const Vector3f& position) {
    // TODO: Implement Quaternion version of lookAt function.
    // transform.rotation = q_lookAt(transform.position, position, {0, 1, 0});
  }

  inline void offsetRotation(float yaw, bool yaw_d, float pitch, bool pitch_d) {
  }

  inline Vector3f forward() const {}

  inline Vector3f right() const {}

  inline Vector3f up() const {}

  inline Vector3f back() const {}

  inline Vector3f left() const {}

  inline Vector3f down() const {}

  inline Matrix4f getMatrix() const {}

  inline Matrix4f getProjection() const {}

  inline Matrix4f getView() const {}

  Transform transform;
  float FOV   = 70.0f; // NOTE *IN DEGREES!*
  float zNear = 0.1f, zFar = 1000.0f, aspect = 4.0 / 3.0;
  bool isPerspective = true; // If not, then orthographic
}

} // namespace Dunjun

#endif

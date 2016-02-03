#ifndef DUNJUN_CAMERA_HPP
#define DUNJUN_CAMERA_HPP

#include <Dunjun/Math/Transform.hpp>
#include <Dunjun/Math/Vector3f.hpp>
#include <Dunjun/Math/Matrix4f.hpp>

namespace Dunjun {

struct Camera {

  inline void lookAt(const Vector3f& dest, const Vector3f& up = {0, 1, 0}) {
    transform.rotation = toQuaternion(m_lookAt(transform.position, dest, up));
  }

  inline void offsetRotation(float yaw, bool yaw_d, float pitch, bool pitch_d) {
    transform.rotation = transform.rotation * Quaternion(pitch, pitch_d, r()) *
                         Quaternion(yaw, yaw_d, {0, 1, 0});
  }

  inline Vector3f f() const {
    return transform.rotation.conjugate() * Vector3f(0, 0, -1);
  }

  inline Vector3f r() const {
    return transform.rotation.conjugate() * Vector3f(1, 0, 0);
  }

  inline Vector3f u() const {
    return transform.rotation.conjugate() * Vector3f(0, 1, 0);
  }

  inline Vector3f b() const {
    return transform.rotation.conjugate() * Vector3f(0, 0, 1);
  }

  inline Vector3f l() const {
    return transform.rotation.conjugate() * Vector3f(-1, 0, 0);
  }

  inline Vector3f d() const {
    return transform.rotation.conjugate() * Vector3f(0, -1, 0);
  }

  inline Matrix4f getProjection() const {
    if (isPerspective) {
      return perspective(FOV, true, aspect, zNear, zFar);
    } else {
      float distance = (zFar - zNear) / 2.0f;
      return ortho(-orthoScale * aspect, orthoScale * aspect, -orthoScale,
                   orthoScale, -distance, distance);
    }
  }

  inline Matrix4f getView() const {
    return scaleMatrix(
               {transform.scale.x, transform.scale.y, transform.scale.z}) *
           transform.rotation.toMatrix() * translateMatrix(-transform.position);
  }

  inline Matrix4f getMatrix() const { return getProjection() * getView(); }

  Transform transform;
  float FOV   = 70.0f; // NOTE *IN DEGREES!*
  float zNear = 0.1f, zFar = 1000.0f, aspect = 4.0 / 3.0;
  bool isPerspective = true; // If not, then orthographic

  float orthoScale = 1.0f; // Scale used for orthographic projection
};

} // namespace Dunjun

#endif

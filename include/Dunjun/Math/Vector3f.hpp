#pragma once
#ifndef DUNJUN_MATH_VECTOR3F_HPP
#define DUNJUN_MATH_VECTOR3F_HPP

namespace Dunjun {
struct Vector3f {
  Vector3f() : x(0), y(0), z(0) {}
  explicit Vector3f(float xyz) : x(xyz), y(xyz), z(xyz) {}
  Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}
  Vector3f(float xy[3]) : x(xy[0]), y(xy[1]), z(xy[2]) {}

  union {
    float data[3];
    struct {
      float x, y, z;
    };
    struct {
      float s, t, p;
    };
  };

  inline float& operator[](std::size_t index) { return data[index]; }
  inline const float& operator[](std::size_t index) const {
    return data[index];
  }
};
} // namespace Dunjun

#endif

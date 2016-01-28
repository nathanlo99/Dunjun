#pragma once
#ifndef DUNJUN_MATH_VECTOR4F_HPP
#define DUNJUN_MATH_VECTOR4F_HPP

namespace Dunjun {
struct Vector4f {
  Vector4f() : x(0), y(0), z(0), w(0) {}
  explicit Vector4f(float xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}
  Vector4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
  Vector4f(float xy[4]) : x(xy[0]), y(xy[1]), z(xy[2]), w(xy[3]) {}

  union {
    float data[4];
    struct {
      float x, y, z, w;
    };
    struct {
      float r, g, b, a;
    };
    struct {
      float s, t, p, q;
    };
  };

  inline float& operator[](std::size_t index) { return data[index]; }
  inline const float& operator[](std::size_t index) const {
    return data[index];
  }
};
} // namespace Dunjun

#endif

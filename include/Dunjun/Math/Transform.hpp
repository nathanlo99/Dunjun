#pragma once
#ifndef DUNJUN_MATH_TRANSFORM_HPP
#define DUNJUN_MATH_TRANSFORM_HPP

#include <Dunjun/Math/Vector3f.hpp>
#include <Dunjun/Math/Matrix4f.hpp>

namespace Dunjun {
Matrix4f identity();

Matrix4f translate(const Vector3f& v);
Matrix4f rotate(float angle, bool degrees, const Vector3f& v);
Matrix4f scale(const Vector3f& v);

Matrix4f ortho(float left, float right, float bottom, float top);
Matrix4f ortho(float left, float right, float bottom, float top, float zNear,
               float zFar);
Matrix4f perspective(float fov, bool degrees, float aspect, float zNear,
                     float zFar);
Matrix4f perspective(float fov, bool degrees, float aspect, float zNear);

Matrix4f lookAt(const Vector3f& eye, const Vector3f& center,
                const Vector3f& up);

} // namespace Dunjun

#endif

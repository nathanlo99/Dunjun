#pragma once
#ifndef DUNJUN_MATH_TRANSFORM_HPP
#define DUNJUN_MATH_TRANSFORM_HPP

#include <Dunjun/Math/Vector3f.hpp>
#include <Dunjun/Math/Matrix4f.hpp>

namespace Dunjun {

Matrix4f translate(const Vector3f& v);
Matrix4f rotate(float angle, const Vector3f& v);
Matrix4f scale(const Vector3f& v);

} // namespace Dunjun

#endif

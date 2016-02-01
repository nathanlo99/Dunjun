#ifndef DUNJUN_VERTEX_HPP
#define DUNJUN_VERTEX_HPP

#include <Dunjun/Color.hpp>

#include <Dunjun/Math/Vector2f.hpp>
#include <Dunjun/Math/Vector3f.hpp>

namespace Dunjun {
struct Vertex {
  Dunjun::Vector3f pos;
  Dunjun::Color color;
  Dunjun::Vector2f texCoords;
};

} // namespace Dunjun
#endif

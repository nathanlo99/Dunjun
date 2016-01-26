#ifndef DUNJUN_TYPES_HPP
#define DUNJUN_TYPES_HPP

#include <cstdint>
#include <cstddef>

namespace Dunjun {
  using int8 = std::int8_t;
  using int16 = std::int16_t;
  using int32 = std::int32_t;
  using int64 = std::int64_t;

  using uint8 = std::uint8_t;
  using uint16 = std::uint16_t;
  using uint32 = std::uint32_t;
  using uint64 = std::uint64_t;

  using float32 = float;
  using float64 = double;

  using size = std::size_t;

  using intptr = std::intptr_t;
  using uintptr = std::uintptr_t;
  
} //namespace Dunjun

#endif

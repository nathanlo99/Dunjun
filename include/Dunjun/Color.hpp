#pragma once
#ifndef DUNJUN_COLOR_HPP
#define DUNJUN_COLOR_HPP

#include <Dunjun/common.hpp>

namespace Dunjun {
union Color {
  u8 data[4];
  struct {
    u8 r, g, b, a;
  };
};
} // namespace Dunjun;

#endif

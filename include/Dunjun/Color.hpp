#pragma once
#ifndef DUNJUN_COLOR_HPP
#define DUNJUN_COLOR_HPP

#include <Dunjun/common.hpp>

namespace Dunjun {
union Color {
  Dunjun::u8 data[4];
  struct {
    Dunjun::u8 r, g, b, a;
  };
};
} // namespace Dunjun;

#endif

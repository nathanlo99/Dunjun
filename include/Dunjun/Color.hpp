#pragma once
#ifndef DUNJUN_COLOR_HPP
#define DUNJUN_COLOR_HPP

#include <Dunjun/common.hpp>

namespace Dunjun {
union Color {
  unsigned char data[4];
  struct {
    unsigned char r, g, b, a;
  };
};
} // namespace Dunjun;

#endif

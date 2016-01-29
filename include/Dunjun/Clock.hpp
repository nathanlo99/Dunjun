#pragma once
#ifndef DUNJUN_CLOCK_HPP
#define DUNJUN_CLOCK_HPP

#include <Dunjun/common.hpp>

namespace Dunjun {
class Clock {
  public:
  double getElapsedTime() const { return glfwGetTime() - m_startTime; }
  void reset() { m_startTime = glfwGetTime(); }
  double restart() {
    double now     = glfwGetTime();
    double elapsed = now - m_startTime;
    m_startTime    = now;
    return elapsed;
  }

  private:
  double m_startTime = glfwGetTime();
};
} // namespace Dunjun

#endif

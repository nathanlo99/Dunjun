#pragma once
#ifndef DUNJUN_TICKCOUNTER_HPP
#define DUNJUN_TICKCOUNTER_HPP

#include <Dunjun/common.hpp>
#include <Dunjun/Clock.hpp>

namespace Dunjun {
class TickCounter {
  public:
  bool update(double frequency) {
    bool reset = false;
    if (m_clock.getElapsedTime() >= frequency) {
      m_tickRate = m_ticks / frequency;
      m_ticks    = 0;
      reset = true;
      m_clock.restart();
    }
    m_ticks++;
    return reset;
  }

  inline std::size_t tickRate() const { return m_tickRate; }

  private:
  std::size_t m_ticks = 0, m_tickRate = 0;
  Clock m_clock;
};
} // namespace Dunjun
#endif

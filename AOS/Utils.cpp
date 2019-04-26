#include "Utils.hpp"
#include "timer.hpp"

double measure(std::function<void(void)> Block) {
  dbt::Timer T;

  T.startClock();
  Block();
  T.stopClock();

  return T.get_us();
}
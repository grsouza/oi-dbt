#pragma once

#include <functional>

/// Measure number of microseconds (us) taken to execute the block.
double measure(std::function<void(void)> Block);
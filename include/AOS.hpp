#pragma once

#include "AOSSolver.hpp"
#include <string>

namespace dbt {
struct AOSParams {
  AOSParams(const std::string &filename);
};

class AOS {
  AOSSolver &solver;

public:
  AOS(const AOSParams &params);
  void Run();
};
};
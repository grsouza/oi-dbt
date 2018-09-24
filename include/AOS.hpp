#pragma once

#include "AOSParams.hpp"
#include "AOSSolver.hpp"

// typedef std::vector<std::string> Threshold;

namespace dbt {

class AOS {
  AOSSolver *solver;

public:
  static AOS create(const std::string &filePath);
  void Run();

private:
  AOS(const AOSParams &params);
};
} // namespace dbt


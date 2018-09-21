#pragma once
#include "AOSSolver.hpp"

namespace dbt {
struct RMHCSolverParams : public AOSSolverParams {
  unsigned generations;
  float mutation;
};

class RMHCSolver : public AOSSolver {
public:
  RMHCSolver(const RMHCSolverParams &params);

  std::vector<std::string> Solve() override;
  void Evaluate() override;
};
};

#pragma once

#include "AOSSolver.hpp"

namespace dbt {

struct GASolverParams : public AOSSolverParams {
  unsigned generations;
};

class GASolver : public AOSSolver {
public:
  GASolver(const GASolverParams &params);
  std::vector<std::string> Solve() override;
  void Evaluate() override;
};

} // namespace dbt


#pragma once

#include "AOSSolver.hpp"

namespace dbt {

struct GASolverParams : public AOSSolverParams {
  unsigned generations;
  float mutationRate;
  unsigned populationSize;
};

class GASolver : public AOSSolver {
  public:
    GASolver(const GASolverParams &params);
    std::vector<std::string> Solve(llvm::Module *M) override;
    void Evaluate() override;
  };
} // namespace dbt


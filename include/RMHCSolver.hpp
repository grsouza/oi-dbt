#pragma once
#include "AOSSolver.hpp"

namespace dbt {
struct RMHCSolverParams : public AOSSolverParams {
  unsigned generations;
  float mutationRate;
};

class RMHCSolver : public AOSSolver {
public:
  RMHCSolver(const RMHCSolverParams &params);

  std::vector<std::string> Solve(llvm::Module *M) override;
  void Evaluate() override;
};
}

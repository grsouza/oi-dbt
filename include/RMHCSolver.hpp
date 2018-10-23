#pragma once
#include "AOSSolver.hpp"

namespace dbt {
struct RMHCSolverParams : public AOSSolverParams {
  unsigned generations;
  float mutationRate;
};

class RMHCSolver : public AOSSolver {
  const RMHCSolverParams &params;

public:
  RMHCSolver(const RMHCSolverParams &params);

  std::vector<std::string> Solve(llvm::Module *M) override;
  void Evaluate() override;

private:
  std::vector<std::string> mutate(const std::vector<std::string> &sequence);
  unsigned fitness(const std::vector<std::string> &sequence);
};
} // namespace dbt

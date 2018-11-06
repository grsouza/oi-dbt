#pragma once

#include "AOSSolver.hpp"
#include "DNA.hpp"

namespace dbt {
struct RMHCSolverParams : public AOSSolverParams {
  unsigned generations;
  float mutationRate;
};

class RMHCSolver : public AOSSolver {
  const RMHCSolverParams &Params;

public:
  RMHCSolver(const RMHCSolverParams &Params);

  std::vector<std::string> Solve(llvm::Module *M) override;
  void Evaluate() override;

private:
  DNA generateInitialDNA();
  DNA mutate(const DNA &D);
};
} // namespace dbt

#pragma once

#include "AOSDatabase.hpp"
#include "AOSSolver.hpp"
#include "DNA.hpp"
#include "SearchSpace.hpp"

namespace dbt {
struct TestModeInfo;

struct RMHCSolverParams : public AOSSolverParams {
  unsigned Size, Max, Min;
  unsigned Generations;
};

class RMHCSolver : public AOSSolver {

  int TotalRegion;
  const RMHCSolverParams &Params;
  std::unique_ptr<DNA> BestEvaluated;

public:
  RMHCSolver(const RMHCSolverParams &Params);

  std::vector<std::string> Solve(llvm::Module *M) override;
  void Solve(llvm::Module *, TestModeInfo) override;
  void Evaluate() override;

private:
  std::unique_ptr<DNA> mutate(const std::vector<std::string> &D);
  std::unique_ptr<DNA> generateInitialDNA();

  enum MutationKind {
    /// Inserts a random pass at end of sequence.
    INSERT,

    /// Randomly selects two positions and swap them.
    SWAP,

    /// Randomly selects a pass and remove it.
    REMOVE,
  };
};
} // namespace dbt

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
  llvm::Module *Mod;
  DNA *BestEvaluated;

public:
  RMHCSolver(const RMHCSolverParams &Params);
  ~RMHCSolver() { delete BestEvaluated; }

  std::vector<uint16_t> Solve(llvm::Module *M) override;
  void Solve(llvm::Module *, TestModeInfo) override;
  void Evaluate() override;

private:
  DNA *mutate(const DNA &D);

  DNA *generateInitialDNA();

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

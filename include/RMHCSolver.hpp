#pragma once

#include "AOSSolver.hpp"
#include "DNA.hpp"
#include "SearchSpace.hpp"

namespace dbt {

struct RMHCSolverParams : public AOSSolverParams {
  unsigned Size, Max, Min;
  unsigned Generations;
  InitPopType SearchSpace;
};

class RMHCSolver : public AOSSolver {
  int TotalRegion;
  const RMHCSolverParams &Params;
  llvm::Module *Mod;
  DNA *BestEvaluated;

public:
  RMHCSolver(const RMHCSolverParams &Params);
  ~RMHCSolver() { delete BestEvaluated; }

  std::vector<std::string> Solve(llvm::Module *M) override;
  void Evaluate() override;

private:
  DNA *mutate(const DNA &D);

  DNA *generateInitialDNA(unsigned GeneSize, InitPopType SearchSpace);
  std::vector<uint16_t> generateRandomGene(unsigned Size);
  std::vector<uint16_t> generateBest10Gene(unsigned Size);
  std::vector<uint16_t> generateBaselineGene(unsigned Size);

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

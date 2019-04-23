#pragma once

#include "AOSDatabase.hpp"
#include "AOSSolver.hpp"
#include "DNA.hpp"
#include "SearchSpace.hpp"

namespace dbt {
struct TestModeInfo;

struct RMHCSolverParams {
  unsigned Size, Max, Min;
  unsigned Generations;
  unsigned Threshold;
};

class RMHCSolver : public AOSSolver {

  RMHCSolverParams Params;
  std::unique_ptr<DNA> BestEvaluated;
  std::vector<double> History;

public:
  RMHCSolver(RMHCSolverParams Params);

  std::vector<std::string> solve(llvm::Module *M) override;

  void Solve(llvm::Module *, TestModeInfo) override;

  std::vector<double> getHistory() const override { return History; }

private:
  static std::unique_ptr<DNA> mutate(const std::vector<std::string> &D);

  static std::unique_ptr<DNA> generateInitialDNA();

  /// If fitness doesn't improve in N generations, then it has stagnated and we
  /// should finish.
  bool hasStagnated(unsigned N);

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

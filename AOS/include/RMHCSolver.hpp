#pragma once

#include "AOSDatabase.hpp"
#include "AOSICSolver.hpp"
#include "AOSParams.hpp"
#include "DNA.hpp"
#include "SearchSpace.hpp"

namespace dbt {
struct ROIInfo;

class RMHCSolver : public AOSICSolver {

  AOSParams::RMHCSolverParams Params;
  std::unique_ptr<DNA> Best;
  std::vector<double> History;

public:
  RMHCSolver(AOSParams::RMHCSolverParams Params)
      : AOSICSolver(), Params(Params) {}

  std::vector<std::string> solve(llvm::Module *M, unsigned) override;
  void solve(llvm::Module *, ROIInfo, unsigned) override;

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

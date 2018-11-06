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
  DNA mutate(const DNA &D);

  DNA generateInitialDNA(unsigned GeneSize, InitPopType Type);
  std::vector<uint16_t> generateRandomGene(unsigned Size);
  std::vector<uint16_t> generateBest10Gene(unsigned Size);
  std::vector<uint16_t> generateBaselineGene(unsigned Size);
};
} // namespace dbt

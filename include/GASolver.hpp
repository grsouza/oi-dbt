#pragma once

#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/Module.h"
#include <llvm/Support/FileSystem.h>

#include "AOSIROpt.hpp"
#include "AOSLog.hpp"
#include "AOSSolver.hpp"
#include "DNA.hpp"
#include "SearchSpace.hpp"
#include <memory>

namespace dbt {

struct GASolverParams : public AOSSolverParams {
  unsigned int generations;
  float mutationRate;
  unsigned int populationSize;
  uint8_t searchSpace;
  unsigned int max, min;
};

class Population {
  unsigned int Size;
  unsigned int Generations;
  std::vector<std::unique_ptr<DNA>> Chromosomes;

public:
  Population(unsigned int, unsigned int, InitPopType);
  void toPrintInfo(std::ofstream &File);
  void calcFitness(llvm::Module *M);
};

class GASolver : public AOSSolver {
  int TotalRegion;
  llvm::Module *Mod;
  const GASolverParams Params;
  std::shared_ptr<Population> Pop;

public:
  GASolver(const GASolverParams &Params)
      : AOSSolver(), Params(Params), TotalRegion(0) {}
  std::vector<std::string> Solve(llvm::Module *) override;
  void Evaluate() override;
};
} // namespace dbt

#pragma once

#include "AOSSolver.hpp"
#include "AOSIROpt.hpp"
#include "AOSLog.hpp"

namespace dbt {
  
  enum InitPopType{ RANDOM, BEST10, BASELINE }; //BASELINE - O1, O2, O3 AND 7 RANDOM
  
  struct GASolverParams : public AOSSolverParams {
    unsigned int generations;
    float mutationRate;
    unsigned int populationSize;
    unsigned int max, min;
  };

  class DNA {
    std::vector<int> Genes;
  public:
    DNA(std::vector<int> Genes) : Genes(std::move(Genes)) {}
    std::vector<int> getGenes();
    void print();
  };

  class Population {
    unsigned int Size; 
  public:
    std::vector<std::unique_ptr<DNA>> Chromosomes;
    Population(unsigned int SizePop, unsigned int SizeGenes, InitPopType Type);
    void print();
  };

  class GASolver : public AOSSolver {
    const GASolverParams Params;
    std::unique_ptr<Population> Pop;
  public:
    GASolver(const GASolverParams &Params) : AOSSolver(), Params(Params) {}
    std::vector<std::string> Solve(llvm::Module *M) override;
    void Evaluate() override;
  };
} // namespace dbt

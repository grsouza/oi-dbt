#pragma once

#include "AOSSolver.hpp"
#include "AOSIROpt.hpp"
#include "AOSLog.hpp"
#include "SearchSpace.hpp"

namespace dbt {
  enum InitPopType{ RANDOM, BEST10, BASELINE }; //BASELINE - O1, O2, O3 AND 7 RANDOM

  struct GASolverParams : public AOSSolverParams {
    unsigned int generations;
    float mutationRate;
    unsigned int populationSize;
    uint8_t searchSpace;
    unsigned int max, min;
  };

  class DNA {
    std::vector<uint16_t> Genes;
  public:
    DNA(std::vector<uint16_t> Genes) : Genes(std::move(Genes)) {}
    std::vector<uint16_t> getGenes();
    void toPrintInfo(std::ofstream &File);
  };

  class Population {
    unsigned int Size; 
    unsigned int Generations;
    std::vector<std::unique_ptr<DNA>> Chromosomes;
  public:
    Population(unsigned int, unsigned int, InitPopType);
    void toPrintInfo(std::ofstream &File);
  };

  class GASolver : public AOSSolver {
    int TotalRegion;
    const GASolverParams Params;
  public:
    GASolver(const GASolverParams &Params) : AOSSolver(), Params(Params), TotalRegion(0) {}
    std::vector<std::string> Solve(llvm::Module*) override;
    void Evaluate() override;
  };
} // namespace dbt

#pragma once

#include "llvm/IR/Module.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include <llvm/Support/FileSystem.h>

#include "AOSSolver.hpp"
#include "AOSIROpt.hpp"
#include "AOSLog.hpp"
#include "SearchSpace.hpp"
#include <memory>

namespace dbt {
  enum InitPopType{ RANDOM, BEST10, BASELINE };

  struct GASolverParams : public AOSSolverParams {
    unsigned int generations;
    float mutationRate;
    float crossoverRate;
    unsigned int populationSize;
    uint8_t searchSpace;
    unsigned int max, min;
  };

  class DNA {
    std::unique_ptr<AOSIROpt> IRO;
    std::unique_ptr<CodeAnalyzer> CA;
    std::vector<uint16_t> Genes;
    int Fitness;
    double Probability;
  public:
    DNA(std::vector<uint16_t> Genes) : Genes(std::move(Genes)) {
      IRO = llvm::make_unique<AOSIROpt>();
      CA = llvm::make_unique<CodeAnalyzer>();
    }
    std::vector<uint16_t> getGenes();
    void calcFitness(std::shared_ptr<llvm::Module>); 
    void normalize(int);
    DNA* crossover(DNA*, int);
    void mutate(float);
    int getFitness() { return Fitness; }
    int getLocus(int index) { return Genes[index]; };
    double getProbability() { return Probability; }
    void toPrintInfo(std::ofstream&);
  };

  class Population {
    unsigned SizeGenes; 
    unsigned Generations;
    std::vector<std::unique_ptr<DNA>> Chromosomes;
    int Best;
  public:
    Population(unsigned, unsigned, InitPopType);
    void toPrintInfo(std::ofstream&);
    void calcFitness(llvm::Module*); 
    void normalize();
    int pickOne();
    void newPoputation(float, float);
    void searchBest(); 
  };

  class GASolver : public AOSSolver {
    int TotalRegion;
    llvm::Module *Mod;
    const GASolverParams Params;
    std::shared_ptr<Population> Pop;
  public:
    GASolver(const GASolverParams &Params) : AOSSolver(), Params(Params), TotalRegion(0) {}
    std::vector<std::string> Solve(llvm::Module*) override;
    void Evaluate() override;
  };
} // namespace dbt

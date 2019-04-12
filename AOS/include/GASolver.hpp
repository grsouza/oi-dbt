#pragma once

// #include "llvm/IR/Module.h"
// #include "llvm/Bitcode/BitcodeWriter.h"
// #include <llvm/Support/FileSystem.h>

// #include "AOSSolver.hpp"
// #include "AOSIROpt.hpp"
// #include "AOSLog.hpp"
// #include "SearchSpace.hpp"
// #include "DNA.hpp"
// #include "AOSDatabase.hpp"

// #include <memory>

// namespace dbt {
//   struct TestModeInfo;
//   struct GASolverParams : public AOSSolverParams {
//     unsigned int Generations;
//     float MutationRate;
//     float CrossoverRate;
//     SearchSpaceType SearchSpace;
//     unsigned int PopulationSize;
//     unsigned int Max, Min;
//   };

//   class Population {
//     unsigned SizeGenes;
//     unsigned Generations;
//     std::vector<std::unique_ptr<GADNA>> Chromosomes;
//     GADNA *Best;
//   public:
//     Population(unsigned, unsigned, SearchSpaceType);

//     void calcFitness(llvm::Module*);
//     void normalize();
//     int pickOne();
//     void newPoputation(float, float);
//     void searchBest();
//     GADNA* getBest() { return Best; }
//     void toPrintInfo(std::ofstream&);
//   };

//   class GASolver : public AOSSolver {
//     int TotalRegion;
//     llvm::Module *M;
//     const GASolverParams Params;
//     std::shared_ptr<Population> CurrentPop;
//   public:
//     GASolver(const GASolverParams &Params) : AOSSolver(), Params(Params),
//       TotalRegion(0) {}
//     std::vector<uint16_t> solve(llvm::Module*) override;
//     void solve(llvm::Module *, TestModeInfo) override;
//     void Evaluate() override;
//   };
// } // namespace dbt

#include "RMHCSolver.hpp"
#include "AOSIROpt.hpp"
#include "DNA.hpp"
#include "SearchSpace.hpp"
#include "manager.hpp"

#include "llvm/IR/Constant.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Transforms/Utils/ValueMapper.h"

using namespace dbt;

std::unique_ptr<DNA> RMHCSolver::solve(llvm::Module *M, unsigned RegionID) {

  Best = generateInitialDNA();
  Best->calculateFitness(std::move(llvm::CloneModule(*M)));
  History.clear();

  unsigned Generation = 0;

  while (Generation < Params.Generations && !hasStagnated(Params.Threshold)) {
    History.push_back(Best->getFitness());

    auto NewDNA = std::move(mutate(Best->getGenes()));
    NewDNA->calculateFitness(std::move(llvm::CloneModule(*M)));

    if (NewDNA->getFitness() < Best->getFitness()) {
      Best = std::move(NewDNA);
    }

    ++Generation;
  }

  return std::move(Best);
}

bool RMHCSolver::hasStagnated(unsigned N) {
  if (History.size() <= N)
    return false;

  size_t Size = History.size();

  return History[Size - N - 1] == History[Size - 1];
}

void RMHCSolver::solve(llvm::Module *M, ROIInfo R, unsigned RegionID) {
  if (RegionID == R.RegionID) {
    auto IRO = std::make_unique<AOSIROpt>();
    IRO->customOptimizeIRFunction(M, R.Opts);
  }
}

std::unique_ptr<DNA> RMHCSolver::generateInitialDNA() {
  return std::make_unique<DNA>(O3_PASSES);
}

std::unique_ptr<DNA> RMHCSolver::mutate(const std::vector<std::string> &D) {
  size_t Size = D.size();

  auto Kind = static_cast<MutationKind>(getRandomNumber(0, 4));

  std::vector<std::string> NewGene = D;

  switch (Kind) {
  case MutationKind::INSERT: {
    NewGene.push_back(O3_PASSES[getRandomNumber(0, O3_PASSES.size())]);
    break;
  }

  case MutationKind::REMOVE: {
    unsigned Idx = getRandomNumber(0, Size);
    NewGene.erase(NewGene.begin() + Idx);
    break;
  }

  case MutationKind::SWAP: {
    unsigned Idx1;
    unsigned Idx2;

    do {
      Idx1 = getRandomNumber(0, Size);
      Idx2 = getRandomNumber(0, Size);
    } while (Idx1 == Idx2);

    std::string Tmp = NewGene[Idx1];
    NewGene[Idx1] = NewGene[Idx2];
    NewGene[Idx2] = Tmp;
    break;
  }
  }

  return std::make_unique<DNA>(NewGene);
}
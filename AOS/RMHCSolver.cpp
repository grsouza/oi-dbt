#include "RMHCSolver.hpp"
#include "DNA.hpp"
#include "SearchSpace.hpp"
#include "manager.hpp"

#include "llvm/IR/Constant.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Transforms/Utils/ValueMapper.h"

using namespace dbt;

RMHCSolver::RMHCSolver(RMHCSolverParams Params) : AOSSolver(), Params(Params) {}

std::vector<std::string> RMHCSolver::solve(llvm::Module *M) {

  BestEvaluated = generateInitialDNA();
  History.clear();

  unsigned Generation = 0;

  while (Generation < Params.Generations && !hasStagnated(300)) {
    History.push_back(
        BestEvaluated->getFitness(std::move(llvm::CloneModule(*M))));

    auto NewDNA = std::move(mutate(BestEvaluated->getGenes()));

    if (NewDNA->getFitness(std::move(llvm::CloneModule(*M))) <
        BestEvaluated->getFitness(std::move(llvm::CloneModule(*M)))) {
      BestEvaluated = std::move(NewDNA);
    }

    ++Generation;
  }

  return BestEvaluated->getGenes();
}

bool RMHCSolver::hasStagnated(unsigned N) {
  if (History.size() <= N)
    return false;

  size_t Size = History.size();

  return History[Size - N - 1] == History[Size - 1];
}

void RMHCSolver::Solve(llvm::Module *, TestModeInfo) {}

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
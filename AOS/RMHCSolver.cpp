#include "RMHCSolver.hpp"
#include "AOSLog.hpp"
#include "DNA.hpp"
#include "SearchSpace.hpp"
#include "manager.hpp"

#include "llvm/IR/Constant.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Transforms/Utils/ValueMapper.h"

using namespace dbt;

RMHCSolver::RMHCSolver(const RMHCSolverParams &Params)
    : AOSSolver(), Params(Params), TotalRegion(0) {}

std::vector<uint16_t> RMHCSolver::Solve(llvm::Module *M) {
  Mod = M;
  LOG->newRegion(++TotalRegion);

  BestEvaluated = generateInitialDNA();
  BestEvaluated->calcFitness(std::move(llvm::CloneModule(*Mod)));

  for (unsigned CurGen = 0; CurGen < Params.Generations; ++CurGen) {
    DNA *NewDNA = mutate(*BestEvaluated);
    NewDNA->calcFitness(std::move(llvm::CloneModule(*Mod)));

    if (NewDNA->getFitness() > BestEvaluated->getFitness()) {
      delete BestEvaluated;
      BestEvaluated = NewDNA;
    }

    // TODO: Check for threshold and break
  }

  Evaluate();
}

void RMHCSolver::Solve(llvm::Module *, TestModeInfo) {}

void RMHCSolver::Evaluate() { LOG->dna(BestEvaluated); }

DNA *RMHCSolver::generateInitialDNA() { return new DNA(O3_PASSES); }

DNA *RMHCSolver::mutate(const DNA &D) {
  const std::vector<std::string> &CurGene = D.getGenes();
  size_t Size = CurGene.size();

  MutationKind Kind = static_cast<MutationKind>(getRandomNumber(0, 4));

  std::vector<std::string> NewGene = CurGene;

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

  return new DNA(NewGene);
}

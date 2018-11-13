#include "RMHCSolver.hpp"
#include "AOSLog.hpp"
#include "SearchSpace.hpp"
#include "llvm/IR/Constant.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Transforms/Utils/ValueMapper.h"

using namespace dbt;

inline int getRandomNumber(int min, int max) { return (rand() % max) + min; }

RMHCSolver::RMHCSolver(const RMHCSolverParams &Params)
    : AOSSolver(), Params(Params), TotalRegion(0) {}

std::vector<std::string> RMHCSolver::Solve(llvm::Module *M) {

  Mod = M;
  LOG->newRegion(++TotalRegion);

  BestEvaluated = generateInitialDNA(Params.Size, Params.SearchSpace);
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

  std::vector<std::string> Sequence;
  return Sequence;
}

void RMHCSolver::Evaluate() { LOG->dna(BestEvaluated); }

DNA *RMHCSolver::generateInitialDNA(unsigned GeneSize,
                                    InitPopType SearchSpace) {
  switch (SearchSpace) {
  case InitPopType::RANDOM:
    return new DNA(generateRandomGene(GeneSize));

  case InitPopType::BEST10:
    return new DNA(generateBest10Gene(GeneSize));

  case InitPopType::BASELINE:
    return new DNA(generateBaselineGene(GeneSize));
  }
}

DNA *RMHCSolver::mutate(const DNA &D) {
  const std::vector<uint16_t> &CurGene = D.getGenes();
  size_t Size = CurGene.size();

  MutationKind Kind = static_cast<MutationKind>(getRandomNumber(0, 4));

  std::vector<uint16_t> NewGene = CurGene;

  switch (Kind) {
  case MutationKind::INSERT: {
    NewGene.push_back(getRandomNumber(OPT_MIN, OPT_MAX + 1));
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

    uint16_t Tmp = NewGene[Idx1];
    NewGene[Idx1] = NewGene[Idx2];
    NewGene[Idx2] = Tmp;
    break;
  }
  }

  return new DNA(NewGene);
}

/** =================================
 * GENE Generation
 ===================================*/

std::vector<uint16_t> RMHCSolver::generateRandomGene(unsigned Size) {
  std::vector<uint16_t> Gene;
  Gene.reserve(Size);

  for (unsigned i = 0; i < Size; ++i)
    Gene.push_back(getRandomNumber(OPT_MIN, OPT_MAX + 1));

  return Gene;
}

std::vector<uint16_t> RMHCSolver::generateBest10Gene(unsigned Size) {
  std::vector<uint16_t> Gene;
  Gene.reserve(Size);

  for (unsigned i = 0; i < Size; ++i)
    Gene.push_back(best10[getRandomNumber(0, best10.size())]);

  return Gene;
}

std::vector<uint16_t> RMHCSolver::generateBaselineGene(unsigned Size) {
  std::vector<uint16_t> Gene;
  Gene.reserve(Size);

  for (unsigned i = 0; i < Size; ++i)
    Gene.push_back(baseline[getRandomNumber(0, baseline.size())]);

  return Gene;
}

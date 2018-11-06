#include "RMHCSolver.hpp"
#include "SearchSpace.hpp"

using namespace dbt;

inline int getRandomNumber(int min, int max) { return (rand() % max) + min; }

RMHCSolver::RMHCSolver(const RMHCSolverParams &Params)
    : AOSSolver(), Params(Params) {}

std::vector<std::string> RMHCSolver::Solve(llvm::Module *M) {

  // TODO:
  // 1. Choose an initial DNA as the current best-evaluated DNA and evaluate its
  // fitness
  // 2. Choose a locus at random to mutate on this DNA.
  // 3. Evaluate the fitness of the new DNA. If it leads to better fitness, set
  // it as the best-evaluated DNA, if not, give it up.
  // 4. If the fitness reaches the threshold return a the best evaluated DNA, if
  // not return step 2.

  DNA BestEvaluated = generateInitialDNA(Params.size, Params.);
  BestEvaluated.calcFitness(std::shared_ptr<llvm::Module>(M));

  for (unsigned CurrentGeneration = 0; CurrentGeneration < Params.generations;
       ++CurrentGeneration) {
    DNA NewDNA = mutate(BestEvaluated);
    NewDNA.calcFitness(std::shared_ptr<llvm::Module>(M));

    if (NewDNA.getFitness() > BestEvaluated.getFitness())
      BestEvaluated = NewDNA;

    // TODO: Check for threshold and break
  }

  std::vector<std::string> Sequence;
  return Sequence;
}

void RMHCSolver::Evaluate() {}

DNA RMHCSolver::generateInitialDNA(unsigned GeneSize, InitPopType Type) {
  switch (Type) {
  case InitPopType::RANDOM:
    return DNA(generateRandomGene(GeneSize));

  case InitPopType::BEST10:
    return DNA(generateBest10Gene(GeneSize));

  case InitPopType::BASELINE:
    return DNA(generateBaselineGene(GeneSize));
  }
}

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

DNA RMHCSolver::mutate(const DNA &D) {
  const std::vector<uint16_t> &CurGene = D.getGenes();
  size_t Size = CurGene.size();
  unsigned Idx1;
  unsigned Idx2;

  do {
    Idx1 = rand() % Size;
    Idx2 = rand() % Size;
  } while (Idx1 == Idx2);

  std::vector<uint16_t> NewSequence = CurGene;
  uint16_t Tmp = NewSequence[Idx1];
  NewSequence[Idx1] = NewSequence[Idx2];
  NewSequence[Idx2] = Tmp;
  return DNA(NewSequence);
}

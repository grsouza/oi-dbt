#include "RMHCSolver.hpp"

using namespace dbt;

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

  DNA BestEvaluated = generateInitialDNA();
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

DNA RMHCSolver::generateInitialDNA() {
  // TODO: implement
}

DNA RMHCSolver::mutate(const DNA &D) {
  std::vector<uint16_t> &CurGene = D.getGenes();
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

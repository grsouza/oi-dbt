#include "DNA.hpp"

using namespace dbt;

double DNA::getFitness(std::shared_ptr<llvm::Module> M) {
  if (FitnessCalculated)
    return Fitness;

  calculateFitness(M);
  return Fitness;
}

void DNA::calculateFitness(std::shared_ptr<llvm::Module> M) {
  IRO->customOptimizeIRFunction(M.get(), Genes);
  Fitness = CA->getIPC(M);
  FitnessCalculated = true;
}

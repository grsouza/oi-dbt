#include "DNA.hpp"

using namespace dbt;

void DNA::calculateFitness(std::shared_ptr<llvm::Module> M) {
  if (FitnessCalculated) return;

  IRO->customOptimizeIRFunction(M.get(), Genes);
  Fitness = CA->getIPC(M);
  FitnessCalculated = true;
}

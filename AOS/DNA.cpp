#include "DNA.hpp"
#include "Utils.hpp"

using namespace dbt;

void DNA::calculateFitness(std::shared_ptr<llvm::Module> M) {
  if (FitnessCalculated)
    return;

  OptTime = measure([&] { IRO->customOptimizeIRFunction(M.get(), Genes); });
  Fitness = CA->getIPC(M);
  FitnessCalculated = true;
}
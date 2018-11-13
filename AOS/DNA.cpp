#include "DNA.hpp"

using namespace dbt;

void DNA::calcFitness(std::shared_ptr<llvm::Module> M) {
  IRO->optimizeIRFunction(M, Genes, AOSIROpt::OptLevel::Basic);
  Fitness = CA->getStaticSize(M);
}

void DNA::toPrintInfo(std::ofstream &File) const {
  File << "  ";
  for (int i = 0; i < Genes.size(); i++) {
    if (i != Genes.size() - 1)
      File << Genes[i] << "-";
    else
      File << Genes[i];
  }
  File << " | F: " << Fitness << "\n";
}

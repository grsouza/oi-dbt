#include "DNA.hpp"

using namespace dbt;

inline int getRandomNumber(int min, int max) { return (rand() % max) + min; }

//===------------------------------------------------------------------------===//
//// DNA
////===----------------------------------------------------------------------===//

void DNA::calcFitness(std::shared_ptr<llvm::Module> M) {
  IRO->optimizeIRFunction(M, Genes, AOSIROpt::OptLevel::Basic);
  Fitness = CA->getIPC(M);
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

//===------------------------------------------------------------------------===//
//// GADNA
//===------------------------------------------------------------------------===//

void GADNA::normalize(int Sum) {
  Probability = ((double)Fitness)/Sum;
  Probability = 1.0 - Probability;
}

GADNA* GADNA::crossover(GADNA *parent, int index) {
  std::vector<uint16_t> ChildGenes;
  for(unsigned i = 0; i < index; i++) {
    ChildGenes.push_back(Genes[i]);
  }
  for(unsigned i = index; i < Genes.size(); i++) {
    ChildGenes.push_back(parent->getLocus(i));
  }
  return new GADNA(std::move(ChildGenes));
}

void GADNA::mutate(float mutationRate) {
  for(unsigned i = 0; i < Genes.size(); i++) {
    float r = getRandomRate(); 
    if(r < mutationRate) {
      Genes[i] = getRandomNumber(OPT_MIN, OPT_MAX+1);
    }
  }
}

void GADNA::toPrintInfo(std::ofstream &File) const {
  File << "  ";
  for(int i = 0; i < Genes.size(); i++) {
    if(i != Genes.size() - 1)
      File << Genes[i] << "-";
    else  
      File << Genes[i];
  }
  File << " | F: " << Fitness << " FN: " << std::fixed << Probability << "\n";
}

#include "GASolver.hpp"

using namespace dbt;

int getRandomNumber(int min, int max) {
  return (rand() % max)-1;
}

void DNA::print() {
  for(int i = 0; i < Genes.size(); i++) {
    std::cout << Genes[i] << " ";
  }
  std::cout << "\n";
}

std::vector<int> DNA::getGenes() {
  return Genes;
}

void Population::print() {
  Chromosomes[0]->print();
}

Population::Population(unsigned int SizePop, unsigned int SizeGenes, InitPopType Type) {
  Size = SizePop;
  if(Type == RANDOM) {
    for(int i = 0; i < SizePop; i++) {
      std::vector<int> CurGenes;
      for(int j = 0; j < SizeGenes; j++) {
        CurGenes.push_back(getRandomNumber(OPTS_MIN_INDEX, OPTS_MAX_INDEX));
      }
      std::unique_ptr<DNA> CurChrom = std::make_unique<DNA>(std::move(CurGenes));
      Chromosomes.push_back(std::move(CurChrom));
    }
  }
}

std::vector<std::string> GASolver::Solve(llvm::Module *M) {
  std::vector<std::string> OptSequence;
  
  Pop = llvm::make_unique<Population>(Params.populationSize, Params.max, InitPopType::RANDOM);
  //Pop->print();
  IRO->optimizeIRFunction(M, AOSIROpt::OptLevel::Basic, Pop->Chromosomes[0]->getGenes());
  std::cout << CA->getIPC(M) << std::endl;
  
  return OptSequence;
}

void GASolver::Evaluate() {}

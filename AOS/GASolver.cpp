#include "GASolver.hpp"

using namespace dbt;

//===----------------------------------------------------------------------===//
//// Generic
////===----------------------------------------------------------------------===//

int getRandomNumber(int min, int max) {
  return (rand() % max) + min;
}

//===----------------------------------------------------------------------===//
//// DNA 
////===----------------------------------------------------------------------===//

std::vector<uint16_t> DNA::getGenes() {
  return Genes;
}

void DNA::toPrintInfo(std::ofstream &File) {
  File << "  ";
  for(int i = 0; i < Genes.size(); i++) {
    File << Genes[i];
  }
  File << "\n";
}

//===----------------------------------------------------------------------===//
//// Population 
////===----------------------------------------------------------------------===//

void Population::toPrintInfo(std::ofstream &File) {
  File << std::endl;
  File << "total generations: " << Generations << std::endl;
  File << "average fitness: " << std::endl;
  File << "total population: " << Chromosomes.size() << std::endl;
  File << "mutation rate: " << std::endl;  
  File << "All chromosomes:" << std::endl;
  for(int i = 0; i < Chromosomes.size(); i++) {
    Chromosomes[i]->toPrintInfo(File);
  }
}

Population::Population(unsigned int SizePop, unsigned int SizeGenes, InitPopType Type) {
  Generations = 0;
  Size = SizePop;
  for(int i = 0; i < SizePop; i++) {
    std::vector<uint16_t> CurGenes;
    if(Type == RANDOM) {
      for(int j = 0; j < SizeGenes; j++) {
        CurGenes.push_back(getRandomNumber(OPT_MIN, OPT_MAX));
      }
    }else if(Type == BEST10) {
      for(int j = 0; j < SizeGenes; j++) {
        CurGenes.push_back(best10[getRandomNumber(0, best10.size())]);
      }
    }else {
      for(int j = 0; j < SizeGenes; j++) {
        CurGenes.push_back(baseline[getRandomNumber(0, baseline.size())]);
      }
    }
    std::unique_ptr<DNA> CurChrom = std::make_unique<DNA>(std::move(CurGenes));
    Chromosomes.push_back(std::move(CurChrom));
  }
}

//===----------------------------------------------------------------------===//
//// GASolver 
////===----------------------------------------------------------------------===//

std::vector<std::string> GASolver::Solve(llvm::Module *M) {
  std::vector<std::string> OptSequence;
  
  TotalRegion++;
  LOG->newRegion(TotalRegion);

  std::shared_ptr<Population> Pop;
  
  switch(Params.searchSpace) { 
    case 1:
      Pop = std::make_shared<Population>(Params.populationSize, Params.max, InitPopType::BASELINE);
      break;
    case 2:
      Pop = std::make_shared<Population>(Params.populationSize, Params.max, InitPopType::BEST10);
      break;
    default:
      Pop = std::make_shared<Population>(Params.populationSize, Params.max, InitPopType::RANDOM);
  }

  LOG->population(Pop);
  //IRO->optimizeIRFunction(M, Pop->Chromosomes[0]->getGenes(), AOSIROpt::OptLevel::Basic);
  //std::cout << CA->getSize(M) << std::endl;
  return OptSequence;
}

void GASolver::Evaluate() {}

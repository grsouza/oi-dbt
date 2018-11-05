#include "GASolver.hpp"

#include "llvm/IR/Constant.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Transforms/Utils/ValueMapper.h"


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

void DNA::calcFitness(std::shared_ptr<llvm::Module> M) {
  IRO->optimizeIRFunction(M, Genes, AOSIROpt::OptLevel::Basic);
  Fitness = CA->getStaticSize(M);
}

void DNA::toPrintInfo(std::ofstream &File) {
  File << "  ";
  for(int i = 0; i < Genes.size(); i++) {
    if(i != Genes.size() - 1)
      File << Genes[i] << "-";
    else  
      File << Genes[i];
  }
  File << " | F: " << Fitness << "\n";
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

void Population::calcFitness(llvm::Module* M) {
  //Chromosomes[0]->calcFitness(M);
  for(int i = 0; i < Chromosomes.size(); i++) {
    Chromosomes[i]->calcFitness(std::move(llvm::CloneModule(*M)));
  }
}

Population::Population(unsigned int SizePop, unsigned int SizeGenes, InitPopType Type) {
  Generations = 0;
  Size = SizePop;
  for(int i = 0; i < SizePop; i++) {
    std::vector<uint16_t> CurGenes;
    if(Type == RANDOM) {
      for(int j = 0; j < SizeGenes; j++) {
        CurGenes.push_back(getRandomNumber(OPT_MIN, OPT_MAX+1));
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
 
  Mod = M;  
  TotalRegion++;
  LOG->newRegion(TotalRegion);

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

  Evaluate();
  
  return OptSequence;
}

void GASolver::Evaluate() {
  Pop->calcFitness(Mod);
  LOG->population(Pop);
}

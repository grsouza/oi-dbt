#include "GASolver.hpp"

#include "llvm/IR/Constant.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Transforms/Utils/ValueMapper.h"

#include "DNA.hpp"

using namespace dbt;

#define INFINITE 100000 

//===------------------------------------------------------------------------===//
//// Generic 
////===----------------------------------------------------------------------===//

std::vector<uint16_t> generateRandomSpace(unsigned Size) {
  std::vector<uint16_t> Space;
  for(int j = 0; j < Size; j++) {
    Space.push_back(getRandomNumber(OPT_MIN, OPT_MAX+1));
  }
  return Space;
}

std::vector<uint16_t> generateBest10Space(unsigned Size) {
  std::vector<uint16_t> Space;
  for(int j = 0; j < Size; j++) {
    Space.push_back(best10[getRandomNumber(0, best10.size())]);
  }
  return Space;
}

std::vector<uint16_t> generateBaselineSpace(unsigned Size) {
  std::vector<uint16_t> Space;
  for(int j = 0; j < Size; j++) {
    Space.push_back(baseline[getRandomNumber(0, baseline.size())]);
  }
  return Space;
}

//===------------------------------------------------------------------------===//
//// Population 
////===----------------------------------------------------------------------===//

void Population::toPrintInfo(std::ofstream &File) {
  File << std::endl;
  File << "total generations: " << Generations << std::endl;
  File << "total population: " << Chromosomes.size() << std::endl;
  File << "best fitness: " << Best << std::endl;  
  File << "All chromosomes:" << std::endl;
  for(int i = 0; i < Chromosomes.size(); i++) {
    Chromosomes[i]->toPrintInfo(File);
  }
}

void Population::calcFitness(llvm::Module* M) {
  for(int i = 0; i < Chromosomes.size(); i++) {
    Chromosomes[i]->calcFitness(std::move(llvm::CloneModule(*M)));
  }
}

Population::Population(unsigned SizeP, unsigned SizeG, SearchSpaceType InitSpace) {
  Best = INFINITE;
  Generations = 0;
  SizeGenes = SizeG;

  for(int i = 0; i < SizeP; i++) {
    std::vector<uint16_t> CurGenes;
    switch(InitSpace) {
      case SearchSpaceType::RANDOM:
        CurGenes = std::move(generateRandomSpace(SizeGenes));
        break;
      case SearchSpaceType::BEST10:
        CurGenes = std::move(generateBest10Space(SizeGenes));
        break;
      case SearchSpaceType::BASELINE:
        CurGenes = std::move(generateBaselineSpace(SizeGenes));
        break;
    }
    
    std::unique_ptr<GADNA> CurChrom = std::make_unique<GADNA>(std::move(CurGenes));
    Chromosomes.push_back(std::move(CurChrom));
  }
}

int Population::pickOne() {
  int index = 0;
  
  float r = getRandomRate();
  while(r > 0 || index == Chromosomes.size()) {
    if(index > Chromosomes.size()) {
      std::cerr << "pickOne trying to access invalid position of population!\n";
      exit(1);    
    }
    r -= Chromosomes[index]->getProbability();
    index++;
  }
  
  if(index > 0)
    index--;
  
  return index;
}

void Population::newPoputation(float mutationRate, float crossoverRate) {
  std::vector<std::unique_ptr<GADNA>> newChromosomes;
  int randomIndex, parentOne, parentTwo;
  while(newChromosomes.size() < Chromosomes.size()) {
    //select two parents
    parentOne = pickOne();
    parentTwo = pickOne();
    //crossover rate 
    float r = getRandomRate();
    randomIndex = getRandomNumber(0, SizeGenes);
    //crossover 
    std::unique_ptr<GADNA> ChildOne(
        Chromosomes[parentOne]->crossover(Chromosomes[parentTwo].get(), randomIndex));
    std::unique_ptr<GADNA> ChildTwo(
        Chromosomes[parentTwo]->crossover(Chromosomes[parentOne].get(), randomIndex));
    //offspring mutate
    ChildOne->mutate(mutationRate);
    ChildTwo->mutate(mutationRate);
    newChromosomes.push_back(std::move(ChildOne));
    newChromosomes.push_back(std::move(ChildTwo));
  }
  Chromosomes = std::move(newChromosomes);
  Generations++;
}

void Population::searchBest() {
  int index = 0;
  for(unsigned i = 1; i < Chromosomes.size(); i++) {
    if(Chromosomes[i]->getFitness() < Chromosomes[index]->getFitness())
      index = i;
  }
  if(Best > Chromosomes[index]->getFitness()) {
    Best = Chromosomes[index]->getFitness();
  }
}

void Population::normalize() {
  int Sum = 0;
  for(unsigned i = 0; i < Chromosomes.size(); i++) {
    Sum += Chromosomes[i]->getFitness();
  }
  for(unsigned i = 0; i < Chromosomes.size(); i++) {
    Chromosomes[i]->normalize(Sum);
  }
}

//===------------------------------------------------------------------------===//
//// GASolver 
////===----------------------------------------------------------------------===//

void GASolver::Solve(llvm::Module *Mod) {
  M = Mod;  
  ++TotalRegion;
  LOG->newRegion(TotalRegion);

  CurrentPop = std::make_shared<Population>(Params.PopulationSize, Params.Max, 
      Params.SearchSpace);
  
  Evaluate();
}

void GASolver::Evaluate() {
  int it = 0; 
  while(it < Params.Generations) {
    CurrentPop->calcFitness(M);
    CurrentPop->searchBest();
    CurrentPop->normalize();
    LOG->population(CurrentPop);
    CurrentPop->newPoputation(Params.MutationRate, Params.CrossoverRate);
    it++;
  }
}

#include "GASolver.hpp"

#include "llvm/IR/Constant.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Transforms/Utils/ValueMapper.h"

using namespace dbt;

#define INFINITE 100000 

//===------------------------------------------------------------------------===//
//// Generic
////===----------------------------------------------------------------------===//

int getRandomNumber(int min, int max) { // min..max-1
  return (rand() % max) + min;
}

float getRandomRate() {
  float r = getRandomNumber(0, 10);
  return (r /= 10);
}

//===------------------------------------------------------------------------===//
//// DNA 
////===----------------------------------------------------------------------===//

std::vector<uint16_t> DNA::getGenes() {
  return Genes;
}

void DNA::calcFitness(std::shared_ptr<llvm::Module> M) {
  IRO->optimizeIRFunction(M, Genes, AOSIROpt::OptLevel::Basic);
  Fitness = CA->getStaticSize(M);
}

void DNA::normalize(int Sum) {
  Probability = ((double)Fitness)/Sum;
  Probability *= 2;
}

DNA* DNA::crossover(DNA *parent, int index) {
  std::vector<uint16_t> ChildGenes;
  for(unsigned i = 0; i < index; i++) {
    ChildGenes.push_back(Genes[i]);
  }
  for(unsigned i = index; i < Genes.size(); i++) {
    ChildGenes.push_back(parent->getLocus(i));
  }
  return new DNA(std::move(ChildGenes));
}

void DNA::mutate(float mutationRate) {
  for(unsigned i = 0; i < Genes.size(); i++) {
    float r = getRandomRate(); 
    if(r < mutationRate) {
      Genes[i] = getRandomNumber(OPT_MIN, OPT_MAX+1);
    }
  }
}

void DNA::toPrintInfo(std::ofstream &File) {
  File << "  ";
  for(int i = 0; i < Genes.size(); i++) {
    if(i != Genes.size() - 1)
      File << Genes[i] << "-";
    else  
      File << Genes[i];
  }
  File << " | F: " << Fitness << " FN: " << std::fixed << Probability << "\n";
}

//===------------------------------------------------------------------------===//
//// Population 
////===----------------------------------------------------------------------===//

void Population::toPrintInfo(std::ofstream &File) {
  double average = 0;
  for(int i = 0; i < Chromosomes.size(); i++) {
    average += Chromosomes[i]->getProbability();
  }
  average = (average/Chromosomes.size())*100;
  File << std::endl;
  File << "total generations: " << Generations << std::endl;
  File << "average fitness: " << std::fixed << average << std::endl;
  File << "total population: " << Chromosomes.size() << std::endl;
  File << "mutation rate: " << std::endl;  
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

Population::Population(unsigned int SizePop, unsigned int SizeG, InitPopType Type) {
  Best = INFINITE;
  Generations = 0;
  SizeGenes = SizeG;
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

int Population::pickOne() {
  int index = 0;
  float r = getRandomRate();
  while(r > 0) {
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
  std::vector<std::unique_ptr<DNA>> newChromosomes;
  int randomIndex, parentOne, parentTwo;
  while(newChromosomes.size() < Chromosomes.size()) {
    parentOne = pickOne();
    parentTwo = pickOne();
    while(parentTwo == parentOne)
      parentTwo = pickOne();
    
    //float r = getRandomRate();
    //if(r < crossoverRate) {
      randomIndex = getRandomNumber(0, SizeGenes);
      std::unique_ptr<DNA> ChildOne(
        Chromosomes[parentOne]->crossover(Chromosomes[parentTwo].get(), randomIndex));
      std::unique_ptr<DNA> ChildTwo(
        Chromosomes[parentTwo]->crossover(Chromosomes[parentOne].get(), randomIndex));
      ChildOne->mutate(mutationRate);
      ChildTwo->mutate(mutationRate);
      newChromosomes.push_back(std::move(ChildOne));
      newChromosomes.push_back(std::move(ChildTwo));
    //}else {
      //copy parent
    //}
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
    std::cout << Best << " " << Chromosomes[index]->getFitness() << std::endl;
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
  int i = 0; 
  while(i < 10) {
    Pop->calcFitness(Mod);
    Pop->searchBest();
    Pop->normalize();
    //LOG->population(Pop);
    Pop->newPoputation(Params.mutationRate, Params.crossoverRate);
    i++;
  }
}
